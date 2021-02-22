//
// Created by wchen on 2/18/21.
//

#include "variables/line_variables.hpp"
LineVariables::LineVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name): VariableSet(-1, name)
{
    local_input_ptr = data_ptr;

    if (!local_input_ptr->E_k0.empty())
    {
        size_t size_E_k0 = local_input_ptr->E_k0.size();
        size_t Ns = local_input_ptr->new_data.sup.scblocks.size();

        s_enk_plus = Eigen::MatrixXd::Zero(size_E_k0, Ns);
        c_n_s = Eigen::MatrixXd::Zero(size_E_k0, Ns);
        t_n_s_over = Eigen::MatrixXd::Zero(size_E_k0, Ns);

        c_e_sw = Eigen::VectorXd::Zero(size_E_k0);
        ref_desbus = Eigen::VectorXd::Zero(size_E_k0);
        ref_oribus = Eigen::VectorXd::Zero(size_E_k0);
        x_ek_sw = Eigen::VectorXd::Zero(size_E_k0);
        x_e_sw0 = Eigen::VectorXd::Zero(size_E_k0);

        size_t var_counter = 0;

        for (size_t idx=0; idx <local_input_ptr->E_k0.size(); idx++)
        {
            int oribus_num;
            int destbus_num;
            std::string bus_i;
            std::tie (oribus_num, destbus_num, bus_i) = local_input_ptr->E_k0.at(idx);
            // there are extra '' around the bus_id string read from E_k0
            bus_i.erase(std::remove(bus_i.begin(), bus_i.end(), '\''), bus_i.end());
            for (auto n: local_input_ptr->new_data.sup.lines)
            {
                if (oribus_num == n.origbus && destbus_num == n.destbus &&  bus_i==n.id)
                {
                    // fetched origbus and desbus are not ordered, use ref_origbus and ref_desbus to help keep track
                    ref_oribus(idx) = n.origbus;
                    ref_desbus(idx) = n.destbus;
                    c_e_sw(idx) = n.csw;
                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(idx, jdx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(idx, jdx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;


                    }

                }
            }

        }
        size_t line_var_size = size_E_k0 * Ns + 2 * size_E_k0;
        SetRows(line_var_size);
    }
    else{
        exit(0);
    }

}

LineVariables::~LineVariables() {}

Eigen::VectorXd LineVariables::GetValues() const
{
    if(GetRows())
    {
        Eigen::VectorXd tmp_x(GetRows());
        Eigen::
    }


}
void LineVariables::SetVariables(const Eigen::VectorXd &x)
{

}

LineVariables::VecBound  LineVariables::GetBounds() const
{

}
