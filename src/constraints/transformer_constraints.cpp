//
// Created by wchen on 3/29/21.
//
#include <constraints/transformer_constraints.hpp>

TransConstraints::TransConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::shared_ptr<TransformerVariables> trans_var_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    trans_var_name = name;
    // number of constraints from eqn(70) and eqn(71), one of them could be (always) emtpy?
    size_t add_cons = trans_var_ptr->eqn70_index.size() + trans_var_ptr->eqn71_index.size();

    size_t eq70_bi, eq71_bi;
    //SetRows(8 * data_ptr->F_k0.size());
    // eqn70 and eqn71 cannot both be empty


    if (trans_var_ptr->eqn70_index.size() == 0 or trans_var_ptr->eqn71_index.size() == 0)
    {
        SetRows(8 * data_ptr->F_k0.size() + add_cons + 1);
    }
    else {
        SetRows(8 * data_ptr->F_k0.size() + add_cons + 2);
    }



}
TransConstraints::~TransConstraints() {}

Eigen::VectorXd TransConstraints::GetValues() const
{
    Eigen::VectorXd trans_cons (GetRows());
    // eqn(60), bounded to zero for those whose swqual = 0
    const Eigen::VectorXd Eqn60 = trans_var_ptr->x_fk_sw - trans_var_ptr->x_f_sw0;
    // eqn(62) - eqn(69) are all bounded to zero
    Eigen::VectorXd tau_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->tau_fk.size());
    const Eigen::VectorXd  Eqn62 = trans_var_ptr->tau_fk - (trans_var_ptr->tau_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix() - trans_var_ptr->tau_f_mid;
    const Eigen::VectorXd  Eqn63  = trans_var_ptr->tau_fk - trans_var_ptr->theta_f_0;

    Eigen::VectorXd theta_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->theta_fk.size());
    const Eigen::VectorXd  Eqn64 = trans_var_ptr->theta_fk - (trans_var_ptr->theta_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix() - trans_var_ptr->theta_f_mid;
    const Eigen::VectorXd  Eqn65  = trans_var_ptr->theta_fk - trans_var_ptr->theta_f_0;

    Eigen::VectorXd b_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->eta_fk.size());
    Eigen::VectorXd g_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->eta_fk.size());
    const Eigen::VectorXd  Eqn66 = trans_var_ptr->g_fk - (trans_var_ptr->g_f_0.array() / trans_var_ptr->eta_fk.array()).matrix();
    const Eigen::VectorXd  Eqn67 = trans_var_ptr->b_fk - (trans_var_ptr->b_f_0.array() / trans_var_ptr->eta_fk.array()).matrix();
    const Eigen::VectorXd  Eqn68 = trans_var_ptr->g_fk - trans_var_ptr->g_f_0;
    const Eigen::VectorXd  Eqn69 = trans_var_ptr->b_fk - trans_var_ptr->b_f_0;

    // one of them should be empty
    Eigen::VectorXd eqn70_cons = Eigen::VectorXd::Zero(trans_var_ptr->eqn70_fkm_vec.size());
    Eigen::VectorXd eqn71_cons = Eigen::VectorXd::Zero(trans_var_ptr->eqn71_fkm_vec.size());

    // transform the eqn70 and eqn71 binary variables back, so that we now which eta, tau, theta it is

    UMP_int_vec_double eqn70_binary_mat, eqn71_binary_mat;

    size_t counter = 0;
    for (auto const &eq70_id : trans_var_ptr->eqn70_index)
    {
        auto const &binary_vec = trans_var_ptr->eqn70_fkm_vec.at(eq70_id);
        std::vector<double> zero_vec (binary_vec.size(), 0.0);

        for (size_t jdx=0; jdx<zero_vec.size(); jdx++)
        {
            zero_vec.at(jdx) =  trans_var_ptr->eq70_binary_variable(counter);
            counter ++;
        }
        eqn70_binary_mat.insert(std::make_pair(eq70_id,zero_vec));

    }

    counter = 0;
    for (auto const &eq71_id : trans_var_ptr->eqn71_index)
    {
        auto const &binary_vec = trans_var_ptr->eqn71_fkm_vec.at(eq71_id);

        std::vector<double> zero_vec (binary_vec.size(), 0.0);
        for (size_t jdx=0; jdx<zero_vec.size(); jdx++)
        {
            zero_vec.at(jdx) =  trans_var_ptr->eq71_binary_variable(counter);
            counter ++;
        }
        eqn71_binary_mat.insert(std::make_pair(eq71_id,zero_vec));

    }

    counter = 0;
    for (auto const &eq70_id : trans_var_ptr->eqn70_index)
    {

        int counter2 = 0;
        std::vector<double> const &tau_fm_array = trans_var_ptr->eqn70_fkm_vec.at(eq70_id);
        std::vector<double> const &eta_fm_array = trans_var_ptr->eta_fkm_vec.at(eq70_id);
        std::vector<double> const &eqn70_binary_array = eqn70_binary_mat.at(eq70_id);

        // n pair of points, n-1 line segments
        for (size_t jdx=0; jdx< tau_fm_array.size() - 1; jdx++)
        {
            // now the equation for each line segment
            double slope = (eta_fm_array.at(jdx) - eta_fm_array.at(jdx+1)) / (tau_fm_array.at(jdx) - tau_fm_array.at(jdx+1));
            double intcp = eta_fm_array.at(jdx) - slope * tau_fm_array.at(jdx);

            if (trans_var_ptr->eta_fk(eq70_id) >= eta_fm_array.at(jdx) and trans_var_ptr->eta_fk(eq70_id) < eta_fm_array.at(jdx+1))
            {
                if (trans_var_ptr->tau_fk(eq70_id) >= tau_fm_array.at(jdx) and trans_var_ptr->tau_fk(eq70_id) < tau_fm_array.at(jdx+1))
                {
                    eqn70_cons(counter2) = eqn70_binary_array.at(eq70_id) * (trans_var_ptr->eta_fk(eq70_id) - slope * trans_var_ptr->tau_fk(eq70_id) - intcp);
                    counter2++;

                }

            }


        }

    }

    for (auto const &eq71_id : trans_var_ptr->eqn71_index)
    {

        int counter2 = 0;
        std::vector<double> const &theta_fm_array = trans_var_ptr->eqn71_fkm_vec.at(eq71_id);
        std::vector<double> const &eta_fm_array = trans_var_ptr->eta_fkm_vec.at(eq71_id);
        std::vector<double> const &eqn71_binary_array = eqn71_binary_mat.at(eq71_id);

        // n pair of points, n-1 line segments
        for (size_t jdx=0; jdx< theta_fm_array.size()-1; jdx++)
        {
            // now the equation for each line segment
            double slope = (eta_fm_array.at(jdx) - eta_fm_array.at(jdx+1)) / (theta_fm_array.at(jdx) - theta_fm_array.at(jdx+1));
            double intcp = eta_fm_array.at(jdx) - slope * theta_fm_array.at(jdx);


            if (trans_var_ptr->eta_fk(eq71_id) >= eta_fm_array.at(jdx) and trans_var_ptr->eta_fk(eq71_id) < eta_fm_array.at(jdx+1))
            {
                if (trans_var_ptr->tau_fk(eq71_id) >= theta_fm_array.at(jdx) and trans_var_ptr->tau_fk(eq71_id) < theta_fm_array.at(jdx+1))
                {
                    eqn71_cons(counter2) = eqn71_binary_array.at(eq71_id) * (trans_var_ptr->eta_fk(eq71_id) - slope * trans_var_ptr->tau_fk(eq71_id) - intcp);
                    counter2++;
                }

            }


        }

    }

    Eigen::VectorXd eqn70_binary_cons, eqn71_binary_cons;
    if (trans_var_ptr->eqn70_index.size() > 0)
    {
        eqn70_binary_cons = Eigen::VectorXd(1);
        eqn70_binary_cons[0] = trans_var_ptr->eq70_binary_variable.array().sum();
    }


    if (trans_var_ptr->eqn71_index.size() > 0)
    {
        eqn71_binary_cons = Eigen::VectorXd(1);
        eqn71_binary_cons[0] = trans_var_ptr->eq71_binary_variable.array().sum();
    }





    //std::cout<<"g_fk = "<<trans_var_ptr->g_fk.transpose()<<std::endl;
    //std::cout<<"eta_fk = "<<trans_var_ptr->eta_fk.transpose()<<std::endl;
    //std::cout<<"Eqn66 = "<<Eqn66.transpose()<<std::endl;
    for (size_t idx=0; idx<trans_var_ptr->local_input_ptr->F_k0.size(); idx++)
    {
        auto fk = trans_var_ptr->local_input_ptr->F_k0.at(idx);

        for (auto const &fk_tau: trans_var_ptr->local_input_ptr->F_tau)
        {
            // condition on eqn(62), f \in F_k0 and F_tau
            if (fk == fk_tau)
            {
                tau_fk_cons(idx) = Eqn62(idx);
            }
            // condition on eqn(63), f \in F_k0 but not in F_tau
            else{
                tau_fk_cons(idx) = Eqn63(idx);
            }

        }

        for (auto const &fk_theta: trans_var_ptr->local_input_ptr->F_theta)
        {
            // condition on eqn(64), f \in F_k and F_theta
            if (fk == fk_theta)
            {
                theta_fk_cons(idx) = Eqn64(idx);
            }
            // condition on eqn(65), f \in F_k but not in F_theta
            else {
                theta_fk_cons(idx) = Eqn65(idx);
            }
        }

        // wrong name, should be F_eta
        for (auto const &fk_eta: trans_var_ptr->local_input_ptr->F_eta)
        {
            // condition on eqn(66) and eqn(67)
            if (fk == fk_eta)
            {
                b_fk_cons(idx) = Eqn66(idx);
                g_fk_cons(idx) = Eqn67(idx);
            }
            // condition on eqn(68) and eqn(69)
            else {
                b_fk_cons(idx) = Eqn68(idx);
                g_fk_cons(idx) = Eqn69(idx);
            }

        }

    }



    // eqn(76)
    // row: Ns, col: size_F_k0, sum over each col with colwise().sum()
    Eigen::VectorXd s_fk_cons = trans_var_ptr->s_fnk_plus.colwise().sum();
    const Eigen::VectorXd &Eqn77_cons = (trans_var_ptr->p_fk_o.array().square() + trans_var_ptr->q_fk_o.array().square()).sqrt().matrix() - s_fk_cons - trans_var_ptr->s_f_over;
    const Eigen::VectorXd &Eqn78_cons = (trans_var_ptr->p_fk_d.array().square() + trans_var_ptr->q_fk_d.array().square()).sqrt().matrix() - s_fk_cons - trans_var_ptr->s_f_over;

    trans_cons << Eqn60, tau_fk_cons, theta_fk_cons, b_fk_cons, g_fk_cons, s_fk_cons, Eqn77_cons, Eqn78_cons, eqn70_cons, eqn71_cons, eqn70_binary_cons, eqn71_binary_cons;
    //trans_cons << Eqn60, tau_fk_cons, theta_fk_cons, b_fk_cons, g_fk_cons, s_fk_cons, Eqn77_cons, Eqn78_cons;

    std::cout<<"I am here"<<std::endl;


    return trans_cons;
}

TransConstraints::VecBound TransConstraints::GetBounds() const
{
    std::cout<<"getbound, getrows ="<<GetRows()<<std::endl;
    VecBound trans_con_bounds(GetRows());
    Eigen::VectorXd upper_bounds(GetRows());
    Eigen::VectorXd lower_bounds(GetRows());
    Eigen::VectorXd eqn60_up_bound =  Eigen::VectorXd::Ones(trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn60_lo_bound =  -1 * Eigen::VectorXd::Ones(trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn62_69_up_bounds = Eigen::VectorXd::Zero(4 * trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn62_69_lo_bounds = Eigen::VectorXd::Zero(4 * trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn76_up_bounds = Eigen::VectorXd::Zero( trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn76_lo_bounds = Eigen::VectorXd::Zero( trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn77_78_up_bounds = Eigen::VectorXd::Zero( 2 * trans_var_ptr->size_F_k0);
    Eigen::VectorXd eqn77_78_lo_bounds = Eigen::VectorXd::Zero( 2 * trans_var_ptr->size_F_k0);

    Eigen::VectorXd eqn70_up_bound = Eigen::VectorXd::Zero( trans_var_ptr->eqn70_fkm_vec.size());
    Eigen::VectorXd eqn70_lo_bound = Eigen::VectorXd::Zero( trans_var_ptr->eqn70_fkm_vec.size());
    Eigen::VectorXd eqn71_up_bound = Eigen::VectorXd::Zero( trans_var_ptr->eqn71_fkm_vec.size());
    Eigen::VectorXd eqn71_lo_bound = Eigen::VectorXd::Zero( trans_var_ptr->eqn71_fkm_vec.size());

    Eigen::VectorXd eqn70_binary_bound, eqn71_binary_bound;

    if (trans_var_ptr->eqn70_index.size() > 0)
    {
        eqn70_binary_bound = Eigen::VectorXd::Ones(1);

    }

    if (trans_var_ptr->eqn71_index.size() > 0)
    {
        eqn71_binary_bound = Eigen::VectorXd::Ones(1);
    }

    // eqn(60), x_fk_sw - x_f_sw0 = 0 if swqual = 0
    eqn60_up_bound = (eqn60_up_bound.array() * trans_var_ptr->swqual_state.array()).matrix();
    eqn60_lo_bound = (eqn60_lo_bound.array() * trans_var_ptr->swqual_state.array()).matrix();

    // well... eqn(70) and eqn(71) hasn't been coded yet, so
    // we might need to relax this bound
    eqn62_69_up_bounds.setConstant(10);
    eqn62_69_lo_bounds.setConstant(-10);
    // eqn(76) bound
    eqn76_up_bounds.setConstant(1e20);
    eqn76_lo_bounds.setConstant(0);
    // enq(77) and eqn(78) bound
    eqn77_78_up_bounds.setConstant(0);
    eqn77_78_lo_bounds.setConstant(-1e20);

    upper_bounds <<eqn60_up_bound,  eqn62_69_up_bounds, eqn76_up_bounds, eqn77_78_up_bounds, eqn70_up_bound, eqn71_up_bound, eqn70_binary_bound, eqn71_binary_bound;
    lower_bounds <<eqn60_lo_bound,  eqn62_69_lo_bounds, eqn76_lo_bounds, eqn77_78_lo_bounds, eqn70_lo_bound, eqn71_lo_bound, eqn70_binary_bound, eqn71_binary_bound;


    for (size_t idx=0; idx<GetRows(); idx++)
    {
        trans_con_bounds.at(idx).upper_ = upper_bounds(idx);
        trans_con_bounds.at(idx).lower_ = lower_bounds(idx);
    }

    return trans_con_bounds;
}

void TransConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    trans_var_ptr = x->GetComponent<TransformerVariables>(trans_var_name);
}
void TransConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{
    if (var_set == trans_var_name)
    {
        /**
        typedef Eigen::Triplet<double> T;
        std::vector<T> transformer_triplets;

         // jacobian for eqn(60)
        for (size_t idx=0; idx<trans_var_ptr->size_F_k0; idx++)
        {
            if (trans_var_ptr->swqual_state(idx) == 0)
            {
                transformer_triplets.push_back(T(idx+trans_var_ptr->s_fnk_plus.size(), idx, 1.0));
            }
        }


        
        jac_block.setFromTriplets(transformer_triplets.begin(), transformer_triplets.end());
        
        
        for (size_t idx=0; idx<trans_var_ptr->size_F_k0; idx++)
        {
            // jacobian for eqn(62, 63)
            transformer_triplets.push_back(T(idx+trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+2*trans_var_ptr->size_F_k0, 1.0));
            // jacobian for eqn(64, 65)
            transformer_triplets.push_back(T(idx+2*trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+3*trans_var_ptr->size_F_k0, 1.0));
            // jacobian for eqn(67), wrt to b_fk
            transformer_triplets.push_back(T(idx+3*trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+4*trans_var_ptr->size_F_k0, 1.0));
            // jacobian for eqn(67), wrt to eta_fk
            transformer_triplets.push_back(T(idx+3*trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+6*trans_var_ptr->size_F_k0, 1.0));
            // jacobian for eqn(66), wrt to g_fk
            transformer_triplets.push_back(T(idx+4*trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+5*trans_var_ptr->size_F_k0, 1.0));
            // jacobian for eqn(66), wrt to eta_fk
            transformer_triplets.push_back(T(idx+4*trans_var_ptr->size_F_k0, idx+trans_var_ptr->s_fnk_plus.size()+6*trans_var_ptr->size_F_k0, 1.0));

        }

      
        
        // s_fnk_plus.size() = s_fnk_plus.rows() * s_fnk_plus.cols()
        Eigen::MatrixXd eqn77_wrt_flat_s_fnk = Eigen::MatrixXd::Zero(trans_var_ptr->size_F_k0, trans_var_ptr->s_fnk_plus.size());
        size_t sum_len = 0;
        for (size_t idx=0; idx<trans_var_ptr->s_fnk_plus.rows(); idx++)
        {
            for (size_t jdx=0; jdx<trans_var_ptr->s_fnk_plus.cols(); jdx++)
            {
              
               // eqn76 wrt flat_s_fnk
               transformer_triplets.push_back(T(jdx+sum_len+5*trans_var_ptr->size_F_k0 , idx, 1.0));
               // eqn77 wrt flat_s_fnk
               transformer_triplets.push_back(T(jdx+sum_len+6*trans_var_ptr->size_F_k0 , idx, 1.0));
                // eqn78 wrt flat_s_fnk
               transformer_triplets.push_back(T(jdx+sum_len+7*trans_var_ptr->size_F_k0 , idx, 1.0));
               // eqn70 wrt falt_s_fnk
            

            }
            sum_len += trans_var_ptr->s_fnk_plus.rows();
           
        }

        




     **/
    }
    

}

