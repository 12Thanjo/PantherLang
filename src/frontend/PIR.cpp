#include "frontend/PIR.h"



namespace panther{
	namespace PIR{


		auto BaseType::Operator::Param::operator==(const Operator::Param& rhs) const noexcept -> bool {
			return this->type == rhs.type && this->kind == rhs.kind;
		};

		auto BaseType::Operator::operator==(const Operator& rhs) const noexcept -> bool {
			return this->params == rhs.params && this->returnType == rhs.returnType;
		};

		

		auto BaseType::operator==(Token::Kind tok_kind) const noexcept -> bool {
			if(this->kind != Kind::Builtin){ return false; }

			return tok_kind == std::get<BuiltinData>(this->data).kind;
		};



		auto BaseType::operator==(const BaseType& rhs) const noexcept -> bool {
			if(this->kind != rhs.kind){ return false; }


			switch(this->kind){
				case BaseType::Kind::Builtin: {
					if(std::get<BuiltinData>(this->data).kind != std::get<BuiltinData>(rhs.data).kind){ return false; }
				} break;

				case BaseType::Kind::Function: {
					if(this->callOperator != rhs.callOperator){ return false; }
				} break;

				case BaseType::Kind::Struct: {
					const StructData& this_data = std::get<StructData>(this->data);
					const StructData& rhs_data = std::get<StructData>(rhs.data);

					if(this_data.name != rhs_data.name){ return false; }
					if(this_data.source != rhs_data.source){ return false; }
				} break;

				default: {
					evo::debugFatalBreak("unknown BaseType::Kind");
				} break;
			};

			return true;
		};




		auto Type::operator==(const Type& rhs) const noexcept -> bool {
			if(this->baseType.id != rhs.baseType.id){ return false; }

			if(this->qualifiers.size() != rhs.qualifiers.size()){ return false; }

			for(size_t i = 0; i < this->qualifiers.size(); i+=1){
				const AST::Type::Qualifier& this_qualifiers = this->qualifiers[i];
				const AST::Type::Qualifier& rhs_qualifiers = rhs.qualifiers[i];

				if(this_qualifiers.isPtr != rhs_qualifiers.isPtr){ return false; }
				if(this_qualifiers.isConst != rhs_qualifiers.isConst){ return false; }
			}

			return true;
		};


		auto Type::isImplicitlyConvertableTo(const Type& rhs) const noexcept -> bool {
			if(this->baseType.id != rhs.baseType.id){ return false; }

			if(this->qualifiers.size() != rhs.qualifiers.size()){ return false; }

			for(size_t i = 0; i < this->qualifiers.size(); i+=1){
				const AST::Type::Qualifier& this_qualifiers = this->qualifiers[i];
				const AST::Type::Qualifier& rhs_qualifiers = rhs.qualifiers[i];

				if(this_qualifiers.isPtr != rhs_qualifiers.isPtr){ return false; }
				if(this_qualifiers.isConst && rhs_qualifiers.isConst == false){ return false; }
			}

			return true;
		};



	};
};
