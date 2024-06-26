#include "frontend/Source.h"


#include "./Tokenizer.h"
#include "./Parser.h"
#include "./SemanticAnalyzer.h"
#include "frontend/SourceManager.h"

namespace panther{


	auto Source::tokenize() noexcept -> bool {
		auto tokenizer = Tokenizer(*this);
		return tokenizer.tokenize();
	};


	auto Source::parse() noexcept -> bool {
		auto parser = Parser(*this);
		return parser.parse();
	};


	auto Source::semantic_analysis_global_idents_and_imports() noexcept -> bool {
		this->semantic_analyzer = new SemanticAnalyzer(*this);
		
		return this->semantic_analyzer->semantic_analysis_global_idents_and_imports();
	};

	
	auto Source::semantic_analysis_global_aliases() noexcept -> bool {
		return this->semantic_analyzer->semantic_analysis_global_aliases();
	};
	

	auto Source::semantic_analysis_global_types() noexcept -> bool {
		return this->semantic_analyzer->semantic_analysis_global_types();
	};
	
	auto Source::semantic_analysis_global_values() noexcept -> bool {
		return this->semantic_analyzer->semantic_analysis_global_values();
	};
	
	auto Source::semantic_analysis_runtime() noexcept -> bool {
		const bool result = this->semantic_analyzer->semantic_analysis_runtime();

		delete this->semantic_analyzer;

		return result;
	};





	//////////////////////////////////////////////////////////////////////
	// getting

	auto Source::getNode(AST::Node::ID node_id) const noexcept -> const AST::Node& {
		return this->nodes[node_id.id];
	};
	auto Source::getToken(Token::ID token_id) const noexcept -> const Token& {
		return this->tokens[token_id.id];
	};



	auto Source::getVarDecl(AST::Node::ID node_id) const noexcept -> const AST::VarDecl& {
		return this->getVarDecl(this->getNode(node_id));
	};
	auto Source::getVarDecl(const AST::Node& node) const noexcept -> const AST::VarDecl& {
		evo::debugAssert(node.kind == AST::Kind::VarDecl, "Node is not a VarDecl");
		return this->var_decls[node.index];
	};


	auto Source::getFunc(AST::Node::ID node_id) const noexcept -> const AST::Func& {
		return this->getFunc(this->getNode(node_id));
	};
	auto Source::getFunc(const AST::Node& node) const noexcept -> const AST::Func& {
		evo::debugAssert(node.kind == AST::Kind::Func, "Node is not a Func");
		return this->funcs[node.index];
	};

	auto Source::getStruct(AST::Node::ID node_id) const noexcept -> const AST::Struct& {
		return this->getStruct(this->getNode(node_id));
	};
	auto Source::getStruct(const AST::Node& node) const noexcept -> const AST::Struct& {
		evo::debugAssert(node.kind == AST::Kind::Struct, "Node is not a Struct");
		return this->structs[node.index];
	};

	auto Source::getTemplatePack(AST::Node::ID node_id) const noexcept -> const AST::TemplatePack& {
		return this->getTemplatePack(this->getNode(node_id));
	};
	auto Source::getTemplatePack(const AST::Node& node) const noexcept -> const AST::TemplatePack& {
		evo::debugAssert(node.kind == AST::Kind::TemplatePack, "Node is not a TemplatePack");
		return this->template_packs[node.index];
	};

	auto Source::getFuncParams(AST::Node::ID node_id) const noexcept -> const AST::FuncParams& {
		return this->getFuncParams(this->getNode(node_id));
	};
	auto Source::getFuncParams(const AST::Node& node) const noexcept -> const AST::FuncParams& {
		evo::debugAssert(node.kind == AST::Kind::FuncParams, "Node is not a FuncParams");
		return this->func_params[node.index];
	};

	auto Source::getConditional(AST::Node::ID node_id) const noexcept -> const AST::Conditional& {
		return this->getConditional(this->getNode(node_id));
	};
	auto Source::getConditional(const AST::Node& node) const noexcept -> const AST::Conditional& {
		evo::debugAssert(node.kind == AST::Kind::Conditional, "Node is not a Conditional");
		return this->conditionals[node.index];
	};


	auto Source::getReturn(AST::Node::ID node_id) const noexcept -> const AST::Return& {
		return this->getReturn(this->getNode(node_id));
	};
	auto Source::getReturn(const AST::Node& node) const noexcept -> const AST::Return& {
		evo::debugAssert(node.kind == AST::Kind::Return, "Node is not a Return");
		return this->returns[node.index];
	};

	auto Source::getAlias(AST::Node::ID node_id) const noexcept -> const AST::Alias& {
		return this->getAlias(this->getNode(node_id));
	};
	auto Source::getAlias(const AST::Node& node) const noexcept -> const AST::Alias& {
		evo::debugAssert(node.kind == AST::Kind::Alias, "Node is not a Alias");
		return this->aliases[node.index];
	};



	auto Source::getPrefix(AST::Node::ID node_id) const noexcept -> const AST::Prefix& {
		return this->getPrefix(this->getNode(node_id));
	};
	auto Source::getPrefix(const AST::Node& node) const noexcept -> const AST::Prefix& {
		evo::debugAssert(node.kind == AST::Kind::Prefix, "Node is not a Prefix");
		return this->prefixes[node.index];
	};

	auto Source::getInfix(AST::Node::ID node_id) const noexcept -> const AST::Infix& {
		return this->getInfix(this->getNode(node_id));
	};
	auto Source::getInfix(const AST::Node& node) const noexcept -> const AST::Infix& {
		evo::debugAssert(node.kind == AST::Kind::Infix, "Node is not a Infix");
		return this->infixes[node.index];
	};

	auto Source::getPostfix(AST::Node::ID node_id) const noexcept -> const AST::Postfix& {
		return this->getPostfix(this->getNode(node_id));
	};
	auto Source::getPostfix(const AST::Node& node) const noexcept -> const AST::Postfix& {
		evo::debugAssert(node.kind == AST::Kind::Postfix, "Node is not a Postfix");
		return this->postfixes[node.index];
	};

	auto Source::getTemplatedExpr(AST::Node::ID node_id) const noexcept -> const AST::TemplatedExpr& {
		return this->getTemplatedExpr(this->getNode(node_id));
	};
	auto Source::getTemplatedExpr(const AST::Node& node) const noexcept -> const AST::TemplatedExpr& {
		evo::debugAssert(node.kind == AST::Kind::TemplatedExpr, "Node is not a TemplatedExpr");
		return this->templated_exprs[node.index];
	};

	auto Source::getFuncCall(AST::Node::ID node_id) const noexcept -> const AST::FuncCall& {
		return this->getFuncCall(this->getNode(node_id));
	};
	auto Source::getFuncCall(const AST::Node& node) const noexcept -> const AST::FuncCall& {
		evo::debugAssert(node.kind == AST::Kind::FuncCall, "Node is not a FuncCall");
		return this->func_calls[node.index];
	};

	auto Source::getInitializer(AST::Node::ID node_id) const noexcept -> const AST::Initializer& {
		return this->getInitializer(this->getNode(node_id));
	};
	auto Source::getInitializer(const AST::Node& node) const noexcept -> const AST::Initializer& {
		evo::debugAssert(node.kind == AST::Kind::Initializer, "Node is not a Initializer");
		return this->initializers[node.index];
	};



	auto Source::getType(AST::Node::ID node_id) const noexcept -> const AST::Type& {
		return this->getType(this->getNode(node_id));
	};
	auto Source::getType(const AST::Node& node) const noexcept -> const AST::Type& {
		evo::debugAssert(node.kind == AST::Kind::Type, "Node is not a Type");
		return this->types[node.index];
	};


	auto Source::getBlock(AST::Node::ID node_id) const noexcept -> const AST::Block& {
		return this->getBlock(this->getNode(node_id));
	};
	auto Source::getBlock(const AST::Node& node) const noexcept -> const AST::Block& {
		evo::debugAssert(node.kind == AST::Kind::Block, "Node is not a Block");
		return this->blocks[node.index];
	};


	auto Source::getLiteral(AST::Node::ID node_id) const noexcept -> const Token& {
		return this->getLiteral(this->getNode(node_id));
	};
	auto Source::getLiteral(const AST::Node& node) const noexcept -> const Token& {
		evo::debugAssert(node.kind == AST::Kind::Literal, "Node is not a Literal");
		return this->getToken(node.token);
	};

	auto Source::getIdent(AST::Node::ID node_id) const noexcept -> const Token& {
		return this->getIdent(this->getNode(node_id));
	};
	auto Source::getIdent(const AST::Node& node) const noexcept -> const Token& {
		evo::debugAssert(node.kind == AST::Kind::Ident, "Node is not a Ident");
		return this->getToken(node.token);
	};

	auto Source::getIntrinsic(AST::Node::ID node_id) const noexcept -> const Token& {
		return this->getIntrinsic(this->getNode(node_id));
	};
	auto Source::getIntrinsic(const AST::Node& node) const noexcept -> const Token& {
		evo::debugAssert(node.kind == AST::Kind::Intrinsic, "Node is not a Intrinsic");
		return this->getToken(node.token);
	};


	auto Source::getUninit(AST::Node::ID node_id) const noexcept -> const Token& {
		return this->getUninit(this->getNode(node_id));
	};
	auto Source::getUninit(const AST::Node& node) const noexcept -> const Token& {
		evo::debugAssert(node.kind == AST::Kind::Uninit, "Node is not a Uninit");
		return this->getToken(node.token);
	};

	auto Source::getUnreachable(AST::Node::ID node_id) const noexcept -> const Token& {
		return this->getUnreachable(this->getNode(node_id));
	};
	auto Source::getUnreachable(const AST::Node& node) const noexcept -> const Token& {
		evo::debugAssert(node.kind == AST::Kind::Unreachable, "Node is not a Unreachable");
		return this->getToken(node.token);
	};



	//////////////////////////////////////////////////////////////////////
	// messaging

	auto Source::fatal(const std::string& msg, uint32_t line, uint32_t collumn) noexcept -> void {
		this->has_errored = true;

		auto message = Message{
			.type     = Message::Type::Fatal,
			.source   = this,
			.message  = msg,
			.location = {
				.line_start    = line,
				.line_end      = line,
				.collumn_start = collumn,
				.collumn_end   = collumn,
			},
		};

		this->source_manager.emitMessage(message);
	};


	auto Source::fatal(const std::string& msg, uint32_t line, uint32_t collumn_start, uint32_t collumn_end) noexcept -> void {
		this->has_errored = true;

		auto message = Message{
			.type     = Message::Type::Fatal,
			.source   = this,
			.message  = msg,
			.location = {
				.line_start    = line,
				.line_end      = line,
				.collumn_start = collumn_start,
				.collumn_end   = collumn_end,
			},
		};

		this->source_manager.emitMessage(message);
	};




	auto Source::error(const std::string& msg, uint32_t line, uint32_t collumn, std::vector<Message::Info>&& infos) noexcept -> void {
		this->error(msg, Location{line, line, collumn, collumn}, std::move(infos));
	};

	auto Source::error(const std::string& msg, Token::ID token_id, std::vector<Message::Info>&& infos) noexcept -> void {
		const Token& token = this->getToken(token_id);
		this->error(msg, token.location, std::move(infos));
	};

	auto Source::error(const std::string& msg, const Token& token, std::vector<Message::Info>&& infos) noexcept -> void {
		this->error(msg, token.location, std::move(infos));
	};

	auto Source::error(const std::string& msg, AST::Node::ID node_id, std::vector<Message::Info>&& infos) noexcept -> void {
		this->error(msg, this->get_node_location(node_id), std::move(infos));
	};

	auto Source::error(const std::string& msg, const AST::Node& node, std::vector<Message::Info>&& infos) noexcept -> void {
		this->error(msg, this->get_node_location(node), std::move(infos));
	};

	auto Source::error(
		const std::string& msg, Location location, std::vector<Message::Info>&& infos
	) noexcept -> void {
		this->has_errored = true;

		auto message = Message{
			.type     = Message::Type::Error,
			.source   = this,
			.message  = msg,
			.location = location,
			.infos	  = std::move(infos),
		};

		this->source_manager.emitMessage(message);
	};




	auto Source::warning(const std::string& msg, uint32_t line, uint32_t collumn, std::vector<Message::Info>&& infos) noexcept -> void {
		this->warning(msg, Location{line, line, collumn, collumn}, std::move(infos));
	};

	auto Source::warning(const std::string& msg, Token::ID token_id, std::vector<Message::Info>&& infos) noexcept -> void {
		const Token& token = this->getToken(token_id);
		this->warning(msg, token.location, std::move(infos));
	};

	auto Source::warning(const std::string& msg, const Token& token, std::vector<Message::Info>&& infos) noexcept -> void {
		this->warning(msg, token.location, std::move(infos));
	};

	auto Source::warning(const std::string& msg, AST::Node::ID node_id, std::vector<Message::Info>&& infos) noexcept -> void {
		this->warning(msg, this->get_node_location(node_id), std::move(infos));
	};

	auto Source::warning(const std::string& msg, const AST::Node& node, std::vector<Message::Info>&& infos) noexcept -> void {
		this->warning(msg, this->get_node_location(node), std::move(infos));
	};


	auto Source::warning(
		const std::string& msg, Location location, std::vector<Message::Info>&& infos
	) noexcept -> void {
		this->has_errored = true;

		auto message = Message{
			.type     = Message::Type::Warning,
			.source   = this,
			.message  = msg,
			.location = location,
			.infos	  = std::move(infos),
		};

		this->source_manager.emitMessage(message);
	};





	auto Source::get_node_location(AST::Node::ID node_id) const noexcept -> Location {
		return this->get_node_location(this->getNode(node_id));
	};




	auto Source::get_node_location(const AST::Node& node) const noexcept -> Location {
		switch(node.kind){
			case AST::Kind::VarDecl: {
				const AST::VarDecl& var_decl = this->getVarDecl(node);
				return this->get_node_location(var_decl.ident);
			} break;

			case AST::Kind::TemplatePack: {
				const AST::TemplatePack& template_pack = this->getTemplatePack(node);
				return this->getToken(template_pack.startTok).location;
			} break;

			case AST::Kind::TemplatedExpr: {
				const AST::TemplatedExpr& templated_expr = this->getTemplatedExpr(node);
				return this->get_node_location(templated_expr.expr);
			} break;

			case AST::Kind::FuncParams: {
				const AST::FuncParams& func_params_block = this->getFuncParams(node);
				return this->getToken(func_params_block.startTok).location;
			} break;

			case AST::Kind::Func: {
				const AST::Func& func = this->getFunc(node);
				return this->get_node_location(func.ident);
			} break;

			case AST::Kind::Struct: {
				const AST::Struct& struct_decl = this->getStruct(node);
				return this->get_node_location(struct_decl.ident);
			} break;

			case AST::Kind::Return: {
				const AST::Return& return_stmt = this->getReturn(node);
				const Token& token = this->getToken(return_stmt.keyword);
				return token.location;
			} break;

			case AST::Kind::Conditional: {
				const AST::Conditional& conditional = this->getConditional(node);
				const Token& token = this->getToken(conditional.ifTok);
				return token.location;
			} break;
			
			case AST::Kind::Alias: {
				const AST::Alias& alias = this->getAlias(node);
				return this->get_node_location(alias.ident);
			} break;



			case AST::Kind::Type: {
				const AST::Type& type = this->getType(node);
				if(type.isBuiltin){
					const Token& token = this->getToken(type.base.token);
					return token.location;
				}else{
					return this->get_node_location(this->getNode(type.base.node));
				}
			} break;

			case AST::Kind::Block: {
				evo::debugFatalBreak("Cannot get location of AST::Block");
			} break;

			case AST::Kind::Prefix: {
				const AST::Prefix& prefix = this->getPrefix(node);
				const Token& op_token = this->getToken(prefix.op);
				return op_token.location;
			} break;

			case AST::Kind::Infix: {
				const AST::Infix& infix = this->getInfix(node);
				const Token& op_token = this->getToken(infix.op);

				if(op_token.kind == Token::get(".")){
					return this->get_node_location(infix.rhs);
				}else{
					return op_token.location;
				}

			} break;

			case AST::Kind::Postfix: {
				const AST::Postfix& postfix = this->getPostfix(node);
				const Token& op_token = this->getToken(postfix.op);
				return op_token.location;
			} break;

			case AST::Kind::FuncCall: {
				const AST::FuncCall& func_call = this->getFuncCall(node);
				return this->get_node_location(func_call.target);
			} break;

			case AST::Kind::Initializer: {
				const AST::Initializer& initializer = this->getInitializer(node);
				return this->get_node_location(initializer.type);
			} break;



			case AST::Kind::Ident: {
				const Token& token = this->getIdent(node);
				return token.location;
			} break;

			case AST::Kind::Intrinsic: {
				const Token& token = this->getIntrinsic(node);
				return token.location;
			} break;

			case AST::Kind::Literal: {
				const Token& token = this->getLiteral(node);
				return token.location;
			} break;

			case AST::Kind::Uninit: {
				const Token& token = this->getUninit(node);
				return token.location;
			} break;

			case AST::Kind::Unreachable: {
				const Token& token = this->getUnreachable(node);
				return token.location;
			} break;

		};

		evo::debugFatalBreak("Unknown node type (cannot get node location)");
	};


	
};
