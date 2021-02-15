#include <variables/load_variables.hpp>

LoadVariables::LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(10, name)
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
                    size_t cblock_size = load.cblocks.size();
                    p_jn_over.at(idx).resize(cblock_size);
                    c_jn.at(idx).resize(cblock_size);
                    p_jkn.at(idx).resize(cblock_size);
                    for (size_t jdx=0; jdx<cblock_size; jdx++)
                    {
                        //p_jn_over.at(idx).at(jdx) = load.cblocks.at(jdx).pmax;
                        p_jn_over.at(idx).at(jdx) = load.cblocks.at(jdx).pmax * load_ref_data->s_tilde_inverse;
                        //c_jn.at(idx).at(jdx) = load.cblocks.at(jdx).c;
                        c_jn.at(idx).at(jdx) = load.cblocks.at(jdx).c * load_ref_data->s_tilde_inverse;
                        p_jkn.at(idx).at(jdx) = 0.0;
                        p_jn_counter++;
                        std::cout<<"bus_id = "<<load.bus<<" c_jn = "<<c_jn.at(idx).at(jdx)<<" p_jn_over = "<<p_jn_over.at(idx).at(jdx)<<std::endl;
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
        size_t num_j = p_jkn.size();
        size_t counter = 0;
        for(size_t idx=0; idx<num_j; idx++)
        {
            for (size_t jdx=0; jdx<p_jkn.at(idx).size(); jdx++)
            {
                tmp_x(counter) = p_jkn.at(idx).at(jdx);
                //std::cout<<"In GetValues,    tmp_x.at("<<counter<<") is mapped to p_jkn ("<<idx<<", "<<jdx<<")"<<std::endl;
                counter++;
            }
        }

        return tmp_x;
    }
    
}
void LoadVariables::SetVariables(const Eigen::VectorXd &x) 
{
    size_t counter=0;

    for (size_t idx=0; idx<p_jkn.size(); idx++)
    {

        for (size_t jdx=0; jdx<p_jkn.at(idx).size(); jdx++)
        {
            p_jkn.at(idx).at(jdx) = x(counter);
            //std::cout<<"In SetVariables, tmp_x.at("<<counter<<") is mapped to p_jkn ("<<idx<<", "<<jdx<<")"<<std::endl;
            counter++;
        }
    }
    

}
LoadVariables::VecBound LoadVariables::GetBounds() const 
{
    VecBound load_bounds(GetRows());
    int counter = 0;
    for(auto each_pj : p_jn_over)
        {
            size_t each_pj_size = each_pj.size();

            for (auto each_p_jn : each_pj)
            {
                load_bounds.at(counter).upper_ = each_p_jn;
                load_bounds.at(counter).lower_ = 0.0;
                counter++;
            }
        }
    return load_bounds;

}
