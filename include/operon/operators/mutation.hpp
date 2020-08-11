/* This file is part of:
 * Operon - Large Scale Genetic Programming Framework
 *
 * Licensed under the ISC License <https://opensource.org/licenses/ISC> 
 * Copyright (C) 2019 Bogdan Burlacu 
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE. 
 */

#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "core/operator.hpp"

namespace Operon {
struct OnePointMutation : public MutatorBase {
    Tree operator()(Operon::Random&, Tree) const override;
};

struct MultiPointMutation : public MutatorBase {
    Tree operator()(Operon::Random&, Tree) const override;
};

struct MultiMutation : public MutatorBase {
    Tree operator()(Operon::Random&, Tree) const override;

    void Add(const MutatorBase& op, double prob)
    {
        operators.push_back(std::ref(op));
        probabilities.push_back(prob);
    }

private:
    std::vector<std::reference_wrapper<const MutatorBase>> operators;
    std::vector<double> probabilities;
};

struct ChangeVariableMutation : public MutatorBase {
    ChangeVariableMutation(const gsl::span<const Variable> vars)
        : variables(vars)
    {
    }

    Tree operator()(Operon::Random&, Tree) const override;

private:
    const gsl::span<const Variable> variables;
};

struct ChangeFunctionMutation : public MutatorBase {
    ChangeFunctionMutation(Grammar g) 
        : grammar(g) 
    {
    }

    Tree operator()(Operon::Random&, Tree) const override;

private:
    Grammar grammar;

};

struct InsertSubtreeMutation : public MutatorBase {
    InsertSubtreeMutation(CreatorBase& creator, size_t maxLength, size_t maxDepth) 
        : creator_(creator)
        , maxLength_(maxLength)
        , maxDepth_(maxDepth)
    {
    }

    Tree operator()(Operon::Random&, Tree) const override;

private:
    std::reference_wrapper<CreatorBase> creator_;
    size_t maxLength_;
    size_t maxDepth_;
};

struct ReplaceSubtreeMutation : public MutatorBase {
    ReplaceSubtreeMutation(CreatorBase& creator, size_t maxLength, size_t maxDepth) 
        : creator_(creator) 
        , maxLength_(maxLength)
        , maxDepth_(maxDepth)
    {
    }

    Tree operator()(Operon::Random&, Tree) const override;

private:
    std::reference_wrapper<CreatorBase> creator_;
    size_t maxLength_;
    size_t maxDepth_;

};

struct ShuffleSubtreesMutation : public MutatorBase {
    Tree operator()(Operon::Random&, Tree) const override;
};

}

#endif
