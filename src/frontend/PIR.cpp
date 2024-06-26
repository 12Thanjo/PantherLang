#include "frontend/PIR.h"

#include "frontend/SourceManager.h"


namespace panther{
	namespace PIR{

		auto Expr::operator==(const Expr& rhs) const noexcept -> bool {
			if(this->kind != rhs.kind){ return false; }

			switch(this->kind){
				case Kind::None:        return true;

				case Kind::Var:         evo::debugFatalBreak("Kind::Var in Expr::Equals() is not supported");
				case Kind::Param:       evo::debugFatalBreak("Kind::Param in Expr::Equals() is not supported");
				case Kind::Uninit:      return true;
				case Kind::FuncCall:    evo::debugFatalBreak("Kind::FuncCall in Expr::Equals() is not supported");
				case Kind::Initializer: evo::debugFatalBreak("Kind::Initializer in Expr::Equals() is not supported");
				case Kind::Prefix:      evo::debugFatalBreak("Kind::Prefix in Expr::Equals() is not supported");
				case Kind::Deref:       evo::debugFatalBreak("Kind::Deref in Expr::Equals() is not supported");
				case Kind::Accessor:    evo::debugFatalBreak("Kind::Accessor in Expr::Equals() is not supported");
				case Kind::Import:      return this->import == rhs.import;

				case Kind::LiteralBool:   return this->boolean == rhs.boolean;
				case Kind::LiteralInt:    return this->integer == rhs.integer;
				case Kind::LiteralFloat:  return this->floatingPoint == rhs.floatingPoint;
				case Kind::LiteralChar:   return this->string == rhs.string;
				case Kind::LiteralString: return this->string == rhs.string;

				default: evo::debugFatalBreak("Unknown expr kind in " __FUNCTION__);
			};
		};


		auto TemplateArg::operator==(const TemplateArg& rhs) const noexcept -> bool {
			if(this->isType != rhs.isType){ return false; }
			if(this->typeID != rhs.typeID){ return false; }

			return this->expr == rhs.expr;
		};


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

					return this_data.templateArgs == rhs_data.templateArgs;
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
