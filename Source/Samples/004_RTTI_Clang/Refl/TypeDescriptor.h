#pragma once
#include "ReflConfig.h"
#include <string>
#include <vector>


namespace Refl
{

class MemberVariable;
class MemberFunction;

class REFL_API TypeDescriptor
{

public:
    const std::string& GetName() const
    {
        return _name;
    }

    const std::vector<MemberVariable>& GetMemberVariables() const {
		return memberVars;
	}

    const std::vector<MemberFunction>& GetMemberFunctions() const {
		return memberFuns;
	}

private:
    std::string _name;
    std::vector<MemberVariable> memberVars;
    std::vector<MemberFunction> memberFuns;
};
}