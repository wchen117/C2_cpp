#include <variables/load_variables.hpp>

LoadVariables::LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(kSpecifyLater, name)
{
    load_ref_data = data_ptr;

    if (!load_ref_data->J_k.empty())
    {
        size_t size_jk = load_ref_data->J_k.size();
        p_jn_over.resize(size_jk);
        c_jn.resize(size_jk);
        p_jkn.resize(size_jk);
        size_t p_jn_counter = 0;
        
        
        for(size_t idx=0; idx<size_jk; idx++)
        {
            int j_num;
            std::string bus_i;
            std::tie (j_num, bus_i) = load_ref_data->J_k.at(idx);
            
            for (auto load : load_ref_data->new_data.sup.loads)
            {
                if (j_num == load.bus)
                {
                    for (auto cblock: load.cblocks)
                    {
                        p_jn_over.at(idx).push_back(cblock.pmax * load_ref_data->s_tilde_inverse);
                        c_jn.at(idx).push_back(cblock.c * load_ref_data->s_tilde_inverse);
                        p_jkn.at(idx).push_back(0.0);
                        p_jn_counter++;
                    }
                      
                }
            }
            
        }
        SetRows(p_jn_counter);
    }
    else {
        std::cout<<"J_k vector is empty, quit!"<<std::endl;
        exit(0);

    }

}
LoadVariables::~LoadVariables() {}

Eigen::VectorXd LoadVariables::GetValues() const 
{
    if  (GetRows())
    {
        Eigen::VectorXd tmp_x(GetRows());
        return tmp_x;
    }
    
}
void LoadVariables::SetVariables(const Eigen::VectorXd &x) 
{

}
LoadVariables::VecBound LoadVariables::GetBounds() const 
{
    VecBound load_bounds(GetRows());
    return load_bounds;

}
