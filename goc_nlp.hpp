#ifndef __GOC_NLP_HPP__
#define __GOC_NLP_HPP__

#include "IpTNLP.hpp"
#include "wrapper_construct.hpp"
using namespace Ipopt;

class GOC_NLP: public TNLP
{
public:
    /** Constructor and Destructor **/
    Wrapper_Construct model_construct("./sample_data/ieee14/scenario_1/");

    virtual GOC_NLP();
    virtual ~GOC_NLP();

    /** implement the eight pure virtual functions in NLP **/
    virtual bool get_nlp_info(
        // output, number of variable x
        Index& n,
        // output, number of constraints g(x)
        Index& m,
        // output, number of non zero elements in jacobian of g(x)
        Index& nnz_jac_g,
        // output, number of non zero elements in hessian of f
        Index& nnz_h_lag,
        // output, whether fortran index or c index 
        IndexStyleEnum& index_style
    );

    virtual bool get_bounds_info(
        // input, number of variables x in the problem
        Index n,
        // output, the lower bounds x^L for the variables x
        Number* x_l,
        // output, the upper bounds x^U for the variables x
        Number* x_u,
        // input, the number of constraints g(x) in the problem
        Index m,
        // output, the lower bounds g^L for the constraints g(x)
        Number* g_l,
        // output, the upper bounds g^U for the constraints g(x)
        Number* g_u 
    );

    virtual bool get_starting_point(
        // input, number of variables, same as n in get_nlp_info()
        Index n,
        // input, if true must provide an initial value of x
        bool init_x,
        // output, the initial values for the primal variable x  
        Number* x,
        // input, if true, must provide an initial value for the bound multiplier z^L and z^U
        bool init_z,
        // output, the initial values for the bound multipliers z^L
        Number* z_L,
        // output, the initial values for the bound multipliers z^U
        Number* z_U,
        // input, number of constraints g(x) same in m in get_nlp_info()
        Index m,
        // input, if true, must provide initial value for the constraint multipliers lambda
        bool init_lambda,
        // output, the initial values for the constraints multipliers, lambda
        Number* lambda  
    );
    
    /** Method to request the value of the objective function**/
    virtual bool eval_f(
    
        // input, number of variables, same as n in get_nlp_info()
        Index n,
        // input, values for the primal variables x at which the objective function f(x)
        // is to be evaluated
        const Number* x,
        // input, false if any evaluation method was previously called with the same values in x
        bool new_x,
        // output, storage for the value of the objective function f(x)
        Number& obj_value 
    );

    virtual bool eval_grad_f(
        // input, number of variables x, same as n in get_nlp_info()
        Index n,
        // input, values for the primal variables x at which the objective function grad_f(x)
        // is to be evaluated
        const Number* x,
        // input, false if any evaluation method was previously called with the same values in x
        bool  new_x,
        // output, array to store values of the gradient of the objective function grad_f(s)
        Number* grad_f
    );

    virtual bool eval_g(
    
        // input, number of variables x, same as n in get_nlp_info()
        Index n,
        // input, values for the primal variables x at which the objective function g(x)
        // is to be evaluated
        const Number* x,
        // input, false if any evaluation method was previously called with the same values in x
        bool new_x,
        // input, number of constraints g(x), same as m in get_nlp_info()
        Index m,
        // output, array to store constraint function values g(x), 
        Number* g
    );

    virtual bool eval_jac_g(
       // input, number of variables x, same as n in get_nlp_info() 
       Index n,
       // input, first call: NULL; later calls: the values for the primal variables x at which
       // the constraint jacobian of g(x) is to be evaluated 
       const Number* x,
       // input, false if any evaluation method was previously called with the same values in x
       bool  new_x,
       // input, number of constraints g(x), same as m in get_nlp_info()
       Index m,
       // input, number of nonzero elements in the jacobian
       Index nele_jac,
       // output, first call: array of length nele_jac  to store the row indices of entries in
       // the jacobian of the constraints, later call: NULL
       Index* iRow,
       // output, first call: array of length nele_jac  to store the col indices of entries in
       // the jacobian of the constraints, later call: NULL
       Index* jCol,
       // output, fist call:NULL; later calls: array of length nele_jac to store the values of Jacobian
       Number* values
    );

    virtual bool eval_h(
        // input, number of variables x, same as n in get_nlp_info()
        Index n,
        // input, first call: NULL; later calls: the values for the primal variables 𝑥 at which the Hessian is to be evaluated
        const Number* x,
        // input, false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise; see also TNLP::eval_f
        bool new_x,
        // input, factor \sigma_f in front of the objective term in the Hessian
        Number obj_factor,
        // input, the number of constraints 𝑔(𝑥) in the problem; it will have the same value that was specified in TNLP::get_nlp_info 
        Index m,
        // input, the values for the constraint multipliers \lambda at which the Hessian is to be evaluated
        const Number* lambda,
        // input, false if any evaluation method was previously called with the same values in lambda, true otherwise
        bool new_lambda,
        // input, the number of nonzero elements in the Hessian; it will have the same value that was specified in TNLP::get_nlp_info
        Index nele_hess,
        // output, first call: array of length nele_hess to store the row indices of entries in the Hessian; later calls: NULL
        Index* iRow,
        // output, first call: array of length nele_hess to store the column indices of entries in the Hessian; later calls: NULL
        Index* jCol,
        // output,  first call: NULL; later calls: array of length nele_hess to store the values of the entries in the Hessian
        Number* values
    );

    virtual void finalize_solution(
        // input, gives status of the algorithm
        SolverReturn status,
        // input, number of variables x, same as n in get_nlp_info()
        Index n,
        // input, the final values for the primal variables
        const Number* x,
        // input, the final values for the lower bound multipliers
        const Number* z_L,
        // input, the final values for the upper bound multipliers
        const Number* z_U,
        // input, the number of constraints g(x), same as m in get_nlp_info()
        Index m,
        // input, the final values of the constraint functions
        const Number* g,
        // input, the final values of the contraint multipliers
        const Number* lambda,
        // input, the final value of the objective function
        Number obj_value,
        // input, provided for expert users
        const IpoptData* ip_data,
        IpoptCalculatedQuantities* ip_cq
   );
private:
   /**@name Methods to block default compiler methods.
    *
    * The compiler automatically generates the following three methods.
    *  Since the default compiler implementation is generally not what
    *  you want (for all but the most simple classes), we usually
    *  put the declarations of these methods in the private section
    *  and never implement them. This prevents the compiler from
    *  implementing an incorrect "default" behavior without us
    *  knowing. (See Scott Meyers book, "Effective C++")
    */
   //@{
   GOC_NLP(
      const GOC_NLP&
   );

   GOC_NLP& operator=(
      const GOC_NLP&
   );
   //@}
};
#endif

