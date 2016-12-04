#pragma once

#include <antlr4-runtime.h>

#include "vm.h"

namespace imq
{
	template<typename T, typename... Args>
	T* createNodeFromToken(antlr4::Token* token, Args&&... args)
	{
		static_assert(std::is_base_of<VNode, T>::value, "T must have a base type of VNode (VExpression, VStatement)");
		return new T(args..., { (int32_t)token->getLine(), (int32_t)token->getCharPositionInLine() });
	}
}