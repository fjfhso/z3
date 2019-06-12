/*++
  Copyright (c) 2017 Microsoft Corporation

  Module Name:

  <name>

  Abstract:

  <abstract>

  Author:
  Nikolaj Bjorner (nbjorner)
  Lev Nachmanson (levnach)

  Revision History:


  --*/
#include "math/lp/nla_solver.h"
#include <map>
#include "math/lp/monomial.h"
#include "math/lp/lp_utils.h"
#include "math/lp/var_eqs.h"
#include "math/lp/factorization.h"
#include "math/lp/nla_solver.h"
#include "math/lp/nla_intervals.h"
namespace nla {

void solver::add_monomial(lpvar v, unsigned sz, lpvar const* vs) {
    m_core->add_monomial(v, sz, vs);
}

bool solver::is_monomial_var(lpvar v) const {
    return m_core->is_monomial_var(v);
}

bool solver::need_check() { return true; }

lbool solver::check(vector<lemma>& l) {
    return m_core->check(l);
}

void solver::push(){
    m_core->push();
}

void solver::pop(unsigned n) {
    m_core->pop(n);
}

    std::ostream& solver::display(std::ostream& out) {
        return m_core->print_monomials(out);
    }

        
solver::solver(lp::lar_solver& s): m_core(alloc(core, s)), m_intervals(m_core, m_res_limit)  {
}

solver::~solver() {
    dealloc(m_core);
}
lp::impq solver::get_upper_bound(lpvar j) const {
    SASSERT(is_monomial_var(j) && m_intervals.monomial_has_upper_bound(j));    
    return m_intervals.get_upper_bound_of_monomial(j);
}

lp::impq solver::get_lower_bound(lpvar j) const {
    SASSERT(is_monomial_var(j) && m_intervals.monomial_has_lower_bound(j));
    return m_intervals.get_lower_bound_of_monomial(j);
}

bool solver::monomial_has_lower_bound(lpvar j) const {
    return m_intervals.monomial_has_lower_bound(j);
}
bool solver::monomial_has_upper_bound(lpvar j) const {
    return m_intervals.monomial_has_upper_bound(j);
}
void solver::get_explanation_of_upper_bound_for_monomial(lpvar j, svector<lp::constraint_index>& expl) const {
    m_intervals.get_explanation_of_upper_bound_for_monomial(j, expl);
}
void solver::get_explanation_of_lower_bound_for_monomial(lpvar j, svector<lp::constraint_index>& expl) const{
    m_intervals.get_explanation_of_lower_bound_for_monomial(j, expl);
}
}