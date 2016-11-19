// {{{ GPL License

// This file is part of gringo - a grounder for logic programs.
// Copyright (C) 2013  Roland Kaminski

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// }}}

#ifndef _GRINGO_CONTROL_HH
#define _GRINGO_CONTROL_HH

#include <gringo/symbol.hh>
#include <gringo/types.hh>
#include <gringo/locatable.hh>
#include <gringo/backend.hh>
#include <gringo/logger.hh>
#include <potassco/clingo.h>
#include <clingo.h>

namespace Gringo {

// {{{1 declaration of SymbolicAtoms

using Control = clingo_control;
using SymbolicAtoms = clingo_symbolic_atoms;
using SymbolicAtomIter = clingo_symbolic_atom_iterator_t;

} // namespace Gringo

struct clingo_symbolic_atoms {
    virtual Gringo::Symbol atom(Gringo::SymbolicAtomIter it) const = 0;
    virtual Potassco::Lit_t literal(Gringo::SymbolicAtomIter it) const = 0;
    virtual bool fact(Gringo::SymbolicAtomIter it) const = 0;
    virtual bool external(Gringo::SymbolicAtomIter it) const = 0;
    virtual Gringo::SymbolicAtomIter next(Gringo::SymbolicAtomIter it) = 0;
    virtual bool valid(Gringo::SymbolicAtomIter it) const = 0;
    virtual Gringo::SymbolicAtomIter begin(Gringo::Sig sig) const = 0;
    virtual Gringo::SymbolicAtomIter begin() const = 0;
    virtual Gringo::SymbolicAtomIter lookup(Gringo::Symbol atom) const = 0;
    virtual bool eq(Gringo::SymbolicAtomIter it, Gringo::SymbolicAtomIter jt) const = 0;
    virtual Gringo::SymbolicAtomIter end() const = 0;
    virtual std::vector<Gringo::Sig> signatures() const = 0;
    virtual size_t length() const = 0;
    virtual ~clingo_symbolic_atoms() noexcept = default;
};

namespace Gringo {

using TheoryData = clingo_theory_atoms;

} // namespace Gringo

struct clingo_theory_atoms {
    enum class TermType {
        Tuple = clingo_theory_term_type_tuple,
        List = clingo_theory_term_type_list,
        Set = clingo_theory_term_type_set,
        Function = clingo_theory_term_type_function,
        Number = clingo_theory_term_type_number,
        Symbol = clingo_theory_term_type_symbol
    };
    enum class AtomType {
        Head,
        Body,
        Directive
    };
    virtual TermType termType(Gringo::Id_t) const = 0;
    virtual int termNum(Gringo::Id_t value) const = 0;
    virtual char const *termName(Gringo::Id_t value) const = 0;
    virtual Potassco::IdSpan termArgs(Gringo::Id_t value) const = 0;
    virtual Potassco::IdSpan elemTuple(Gringo::Id_t value) const = 0;
    // This shall map to ids of literals in aspif format.
    virtual Potassco::LitSpan elemCond(Gringo::Id_t value) const = 0;
    virtual Gringo::Lit_t elemCondLit(Gringo::Id_t value) const = 0;
    virtual Potassco::IdSpan atomElems(Gringo::Id_t value) const = 0;
    virtual Potassco::Id_t atomTerm(Gringo::Id_t value) const = 0;
    virtual bool atomHasGuard(Gringo::Id_t value) const = 0;
    virtual Potassco::Lit_t atomLit(Gringo::Id_t value) const = 0;
    virtual std::pair<char const *, Gringo::Id_t> atomGuard(Gringo::Id_t value) const = 0;
    virtual Potassco::Id_t numAtoms() const = 0;
    virtual std::string termStr(Gringo::Id_t value) const = 0;
    virtual std::string elemStr(Gringo::Id_t value) const = 0;
    virtual std::string atomStr(Gringo::Id_t value) const = 0;
    virtual ~clingo_theory_atoms() noexcept = default;
};

namespace Gringo {

} // namespace Gringo

#endif // _GRINGO_CONTROL_HH

