#include <variables/load_variables.hpp>

LoadVariables::LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name)
{
    load_ref_data = data_ptr;

    if (!load_ref_data->J_k0.empty())
    {
        size_t size_jk0 = load_ref_data->J_k0.size();
        // three vectors of vectors
        p_jn_over.resize(size_jk0);
        c_jn.resize(size_jk0);
        p_jkn.resize(size_jk0);
        // now all eigen::vectorxd

        t_jk = Eigen::VectorXd::Zero(size_jk0);
        t_j_over = Eigen::VectorXd::Zero(size_jk0);
        t_j_under = Eigen::VectorXd::Zero(size_jk0);

        q_jk = Eigen::VectorXd::Zero(size_jk0);
        p_j_ru_over = Eigen::VectorXd::Zero(size_jk0);
        p_j_rd_over = Eigen::VectorXd::Zero(size_jk0);
        p_j_0 = Eigen::VectorXd::Zero(size_jk0);
        q_j_0 = Eigen::VectorXd::Zero(size_jk0);

        load_i = Eigen::VectorXi::Zero(size_jk0);
        load_id_j = Eigen::VectorXi ::Zero(size_jk0);
        size_t p_jn_counter = 0;
        
        
        for(size_t idx=0; idx<size_jk0; idx++)
        {
            int j_num;
            std::string bus_i;
            // if written this J_k0 is not ordered at all
            // we use a vector load_j_id to keep track the ordering of
            // j in p_jkn, c_jn, p_jn_over, t_jk, t_j_over, t_j_under
            auto load_key =  load_ref_data->J_k0.at(idx);
            std::tie (j_num, bus_i) = load_key;
            q_jk(idx) = 0.0;
            p_j_0(idx) = load_ref_data->p_l.at(load_key) * load_ref_data->s_tilde_inverse;
            q_j_0(idx) = load_ref_data->q_l.at(load_key) * load_ref_data->s_tilde_inverse;
            // bus_i = "'1'", so we need to get rid of the '' before comparing to load.id
            bus_i.erase(std::remove(bus_i.begin(), bus_i.end(), '\''), bus_i.end());

            for (auto load : load_ref_data->new_data.sup.loads)
            {
                if (j_num == load.bus && bus_i == load.id)
                {
                    size_t cblock_size = load.cblocks.size();
                    p_jn_over.at(idx).resize(cblock_size);
                    c_jn.at(idx).resize(cblock_size);
                    p_jkn.at(idx).resize(cblock_size);
                    t_jk(idx) = 0.5;
                    load_i(idx) = load.bus;
                    load_id_j(idx) = stoi(load.id);
                    t_j_over(idx) = load.tmax;
                    t_j_under(idx) = load.tmin;

                    p_j_ru_over(idx) = load.prumax * load_ref_data->s_tilde_inverse;
                    p_j_rd_over(idx) = load.prdmax * load_ref_data->s_tilde_inverse;

                    for (size_t jdx=0; jdx<cblock_size; jdx++)
                    {
                        //p_jn_over.at(idx).at(jdx) = load.cblocks.at(jdx).pmax;
                        p_jn_over.at(idx).at(jdx) = load.cblocks.at(jdx).pmax * load_ref_data->s_tilde;
                        //c_jn.at(idx).at(jdx) = load.cblocks.at(jdx).c;
                        c_jn.at(idx).at(jdx) = load.cblocks.at(jdx).c * load_ref_data->s_tilde;
                        p_jkn.at(idx).at(jdx) = 0.5;
                        p_jn_counter++;
                        //std::cout<<"bus_id = "<<load.bus<<" c_jn = "<<c_jn.at(idx).at(jdx)<<" p_jn_over = "<<p_jn_over.at(idx).at(jdx)<<std::endl;
                    }
                      
                }
            }
            
        }
        p_jkn_size = p_jn_counter;
        p_jk_size = p_jkn.size();
        t_jk_size = t_jk.size();
        // flattened p_jkn + q_jk + t_jk
        size_t load_var_len = p_jkn_size+2*t_jk_size;
        SetRows(load_var_len);
        //assert(GetRows() == p_jn_counter);
    }
    else {
        std::cout<<"J_k vector is empty, quit!"<<std::endl;
        exit(0);

    }

}
LoadVariables::~LoadVariables() {}

Eigen::VectorXd LoadVariables::GetValues() const 
{
    // in VariableSet GetRows return number of variables
    if  (GetRows())
    {
        Eigen::VectorXd tmp_x(GetRows());
        Eigen::VectorXd flat_p_jkn(p_jkn_size);
        size_t counter = 0;
        for(size_t idx=0; idx<p_jkn.size(); idx++)
        {
            for (size_t jdx=0; jdx<p_jkn.at(idx).size(); jdx++)
            {
                flat_p_jkn(counter) = p_jkn.at(idx).at(jdx);
                counter++;
            }

        }
        tmp_x << flat_p_jkn, q_jk, t_jk;

        // and we are going to add t_jk to variables
        return tmp_x;
    }
    else
    {
        exit(0);
    }
    
}
void LoadVariables::SetVariables(const Eigen::VectorXd &x) 
{
    size_t counter=0;
    auto flat_p_jkn = x.segment(0, p_jkn_size);
    q_jk = x.segment(p_jkn_size, t_jk_size);
    t_jk = x.segment(p_jkn_size+t_jk_size, t_jk_size);


    for (size_t idx=0; idx<p_jkn.size(); idx++)
    {

        for (size_t jdx=0; jdx<p_jkn.at(idx).size(); jdx++)
        {
            p_jkn.at(idx).at(jdx) = flat_p_jkn(counter);
            //std::cout<<"In SetVariables, tmp_x.at("<<counter<<") is mapped to p_jkn ("<<idx<<", "<<jdx<<")"<<std::endl;
            counter++;
        }
    }


    

}
Eigen::VectorXd LoadVariables::get_p_jk() {

    Eigen::VectorXd p_jk = Eigen::VectorXd::Zero(p_jkn.size());

    for (size_t idx=0; idx<p_jkn.size(); idx++)
    {
        for (size_t jdx=0; jdx<p_jkn.at(idx).size(); jdx++)
        {
            p_jk(idx) += p_jkn.at(idx).at(jdx);
        }
    }

    return p_jk;

}
Eigen::VectorXd LoadVariables::get_q_jk()
{
    return q_jk;
}

LoadVariables::VecBound LoadVariables::GetBounds() const 
{
    VecBound load_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());
    // upper and lower bound for p_jkn
    Eigen::VectorXd p_jkn_lower = Eigen::VectorXd::Zero(p_jkn_size);
    Eigen::VectorXd p_jkn_upper = Eigen::VectorXd::Zero(p_jkn_size);
    // so.... it doesn't seem like q_jk has bound at this point, we will code its equality constraint in load_constraints
    Eigen::VectorXd q_jk_upper = Eigen::VectorXd::Zero(t_jk_size);
    q_jk_upper.setConstant(1.0e20);
    Eigen::VectorXd q_jk_lower = Eigen::VectorXd::Zero(t_jk_size);
    q_jk_lower.setConstant(-1.0e20);
    // upper and lower bound for t_jk
    Eigen::Map<const Eigen::VectorXd> t_jk_lower(t_j_under.data(), t_j_under.size());
    Eigen::Map<const Eigen::VectorXd> t_jk_upper(t_j_over.data(), t_j_over.size());

    int counter = 0;
    for(auto each_pj : p_jn_over)
    {
            size_t each_pj_size = each_pj.size();
            for (auto each_p_jn : each_pj)
            {
                p_jkn_upper(counter) = each_p_jn;
                p_jkn_lower(counter) = 0.0;
                counter++;
                //std::cout<<"upper bounds are: "<<each_p_jn<<std::endl;
            }
    }

    upper_bound << p_jkn_upper, q_jk_upper, t_jk_upper;
    lower_bound << p_jkn_lower, q_jk_lower, t_jk_lower;


    for (size_t idx=0; idx<load_bounds.size(); idx++)
    {
        load_bounds.at(idx).upper_ = upper_bound(idx);
        load_bounds.at(idx).lower_ = lower_bound(idx);
    }



    return load_bounds;

}
