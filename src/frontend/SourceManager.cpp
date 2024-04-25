#include "frontend/SourceManager.h"



namespace panther{


	auto SourceManager::addSource(std::filesystem::path&& location, std::string&& data) noexcept -> Source::ID {
		evo::debugAssert(this->isLocked() == false, "Can only add sources to SourceManager when it is locked");

		const auto src_id = Source::ID( uint32_t(this->sources.size()) );

		this->sources.emplace_back(std::move(location), std::move(data), *this, src_id);

		return src_id;
	};



	//////////////////////////////////////////////////////////////////////
	// locked


	auto SourceManager::emitMessage(const Message& msg) const noexcept -> void {
		evo::debugAssert(this->isLocked(), "Can only emit messages when locked");


		this->message_callback(msg);
	};




	// auto SourceManager::getSource(Source::ID id) noexcept -> Source& {
	// 	evo::debugAssert(id.id < this->sources.size(), "Attempted to get invalid source file id");
	// 	evo::debugAssert(this->isLocked(), "Can only get sources when locked");

	// 	return this->sources[id.id];
	// };

	auto SourceManager::getSource(Source::ID id) const noexcept -> const Source& {
		evo::debugAssert(id.id < this->sources.size(), "Attempted to get invalid source file id");
		evo::debugAssert(this->isLocked(), "Can only get sources when locked");

		return this->sources[id.id];
	};


	auto SourceManager::getSourceID(const std::filesystem::path& file_location, std::string_view src_path) const noexcept
		-> evo::Expected<Source::ID, GetSourceIDError>
	{
		// check is valid path
		if(src_path.empty()){ return evo::Unexpected(GetSourceIDError::EmptyPath); }

		std::filesystem::path relative_dir = file_location;
		relative_dir.remove_filename();

		// generate path
		const std::filesystem::path lookup_path = [&]() noexcept {
			if(src_path.starts_with("./")){
				return relative_dir / std::filesystem::path(src_path.substr(2));

			}else if(src_path.starts_with(".\\")){
				return relative_dir / std::filesystem::path(src_path.substr(3));

			// }else if(src_path.starts_with("/") || src_path.starts_with("\\")){
			// 	return relative_dir / std::filesystem::path(src_path.substr(1));

			}else if(src_path.starts_with("../") || src_path.starts_with("..\\")){
				return relative_dir / std::filesystem::path(src_path);

			}else{
				return this->config.basePath / std::filesystem::path(src_path);
			}
		}().lexically_normal();

		if(file_location == lookup_path){
			return evo::Unexpected(GetSourceIDError::SameAsCaller);
		}

		// look for path
		for(size_t i = 0; i < this->sources.size(); i+=1){
			const Source& source = this->sources[i];

			if(source.getLocation() == lookup_path){
				return Source::ID(uint32_t(i));
			}
		}


		if(evo::fs::exists(lookup_path.string())){
			return evo::Unexpected(GetSourceIDError::NotOneOfSources);			
		}

		return evo::Unexpected(GetSourceIDError::DoesntExist);
	};


	auto SourceManager::getSources() noexcept -> std::vector<Source>& {
		evo::debugAssert(this->isLocked(), "Can only get sources when locked");

		return this->sources;
	};

	auto SourceManager::getSources() const noexcept -> const std::vector<Source>& {
		evo::debugAssert(this->isLocked(), "Can only get sources when locked");

		return this->sources;
	};




	// TODO: multithreading
	auto SourceManager::tokenize() noexcept -> evo::uint {
		evo::debugAssert(this->isLocked(), "Can only tokenize when locked");

		evo::uint total_fails = 0;

		for(Source& source : this->sources){
			if(source.tokenize() == false){
				total_fails += 1;
			}
		}


		return total_fails;
	};


	// TODO: multithreading
	auto SourceManager::parse() noexcept -> evo::uint {
		evo::debugAssert(this->isLocked(), "Can only parse when locked");

		evo::uint total_fails = 0;

		for(Source& source : this->sources){
			if(source.parse() == false){
				total_fails += 1;
			}
		}


		return total_fails;
	};


	auto SourceManager::initBuiltinTypes() noexcept -> void {
		evo::debugAssert(this->isLocked(), "Can only initialize builtin types when locked");

		// Import (0)
		this->base_types.emplace_back(PIR::BaseType::Kind::Import);
		this->types.emplace_back( PIR::Type(PIR::BaseType::ID(0)) );

		// Int (1)
		this->base_types.emplace_back(PIR::BaseType::Kind::Builtin, Token::TypeInt);
		this->types.emplace_back( PIR::Type(PIR::BaseType::ID(1)) );

		// Bool (2)
		this->base_types.emplace_back(PIR::BaseType::Kind::Builtin, Token::TypeBool);
		this->types.emplace_back( PIR::Type(PIR::BaseType::ID(2)) );

		// String (3)
		this->base_types.emplace_back(PIR::BaseType::Kind::Builtin, Token::TypeString);
		this->types.emplace_back( PIR::Type(PIR::BaseType::ID(3)) );
	};


	// TODO: optimize base types
	auto SourceManager::initIntrinsics() noexcept -> void {
		evo::debugAssert(this->isLocked(), "Can only initialize intrinsics when locked");
		

		{ // import()
			auto base_type = PIR::BaseType(PIR::BaseType::Kind::Function);
			base_type.callOperator = PIR::BaseType::Operator(
				std::vector<PIR::BaseType::Operator::Param>{ {this->getTypeString(), AST::FuncParams::Param::Kind::Read} },
				this->getTypeImport()
			);

			const PIR::BaseType::ID base_type_id = this->createBaseType(std::move(base_type));
			this->intrinsics.emplace_back(PIR::Intrinsic::Kind::import, "import", base_type_id);
		}

		{ // breakpoint()
			auto base_type = PIR::BaseType(PIR::BaseType::Kind::Function);
			base_type.callOperator = PIR::BaseType::Operator(std::vector<PIR::BaseType::Operator::Param>{}, PIR::Type::VoidableID::Void());

			const PIR::BaseType::ID base_type_id = this->createBaseType(std::move(base_type));
			this->intrinsics.emplace_back(PIR::Intrinsic::Kind::breakpoint, "breakpoint", base_type_id);
		}


		{ // __printHelloWorld()
			auto base_type = PIR::BaseType(PIR::BaseType::Kind::Function);
			base_type.callOperator = PIR::BaseType::Operator(std::vector<PIR::BaseType::Operator::Param>{}, PIR::Type::VoidableID::Void());

			const PIR::BaseType::ID base_type_id = this->createBaseType(std::move(base_type));
			this->intrinsics.emplace_back(PIR::Intrinsic::Kind::__printHelloWorld, "__printHelloWorld", base_type_id);
		}


		{ // __printInt()
			auto base_type = PIR::BaseType(PIR::BaseType::Kind::Function);
			base_type.callOperator = PIR::BaseType::Operator(
				std::vector<PIR::BaseType::Operator::Param>{ {this->getTypeInt(), AST::FuncParams::Param::Kind::Read} },
				PIR::Type::VoidableID::Void()
			);

			const PIR::BaseType::ID base_type_id = this->createBaseType(std::move(base_type));
			this->intrinsics.emplace_back(PIR::Intrinsic::Kind::__printInt, "__printInt", base_type_id);
		}

	};



	// TODO: multithreading
	auto SourceManager::semanticAnalysis() noexcept -> evo::uint {
		evo::debugAssert(this->isLocked(), "Can only do semantic analysis when locked");


		evo::uint total_fails = 0;

		for(Source& source : this->sources){
			if(source.semantic_analysis_declarations() == false){
				total_fails += 1;
			}
		}

		if(total_fails != 0){ return total_fails; }

		for(Source& source : this->sources){
			if(source.semantic_analysis() == false){
				total_fails += 1;
			}
		}

		return total_fails;
	};



	//////////////////////////////////////////////////////////////////////
	// objects

	auto SourceManager::createBaseType(PIR::BaseType&& base_type) noexcept -> PIR::BaseType::ID {
		for(size_t i = 0; i < this->base_types.size(); i+=1){
			if(base_type == this->base_types[i]){
				return PIR::BaseType::ID( uint32_t(i) );
			}
		}


		this->base_types.emplace_back(std::move(base_type));
		return PIR::BaseType::ID( uint32_t(this->base_types.size() - 1) );
	};


	auto SourceManager::getBaseType(Token::Kind tok_kind) noexcept -> PIR::BaseType& {
		for(PIR::BaseType& base_type : this->base_types){
			if(base_type == tok_kind){
				return base_type;
			}
		}

		EVO_FATAL_BREAK("Cannot get unknown builtin base type");
	};


	auto SourceManager::getBaseTypeID(Token::Kind tok_kind) const noexcept -> PIR::BaseType::ID {
		for(size_t i = 0; i < this->base_types.size(); i+=1){
			const PIR::BaseType& base_type = this->base_types[i];

			if(base_type == tok_kind){
				return PIR::BaseType::ID( uint32_t(i) );
			}
		}

		EVO_FATAL_BREAK("Cannot get unknown builtin base type");
	};



	auto SourceManager::getOrCreateTypeID(const PIR::Type& type) noexcept -> PIR::Type::ID {
		// find existing type
		for(size_t i = 0; i < this->types.size(); i+=1){
			const PIR::Type& type_ref = this->types[i];

			if(type_ref == type){
				return PIR::Type::ID( uint32_t(i) );
			}
		}


		// create new type
		this->types.emplace_back(type);
		return PIR::Type::ID( uint32_t(this->types.size() - 1) );
	};

	auto SourceManager::getTypeID(const PIR::Type& type) const noexcept -> PIR::Type::ID {
		// find existing type
		for(size_t i = 0; i < this->types.size(); i+=1){
			const PIR::Type& type_ref = this->types[i];

			if(type_ref == type){
				return PIR::Type::ID( uint32_t(i) );
			}
		}

		EVO_FATAL_BREAK("Unknown type");
	};



	auto SourceManager::printType(PIR::Type::ID id) const noexcept -> std::string {
		const PIR::Type& type = this->getType(id);
		const PIR::BaseType& base_type = this->base_types[type.baseType.id];


		std::string base_type_str = [&]() noexcept {
			switch(base_type.kind){
				case PIR::BaseType::Kind::Import: {
					return std::string("[[IMPORT]]");
				} break;

				case PIR::BaseType::Kind::Builtin: {
					return std::string( Token::printKind(base_type.builtin.kind) );
				} break;

				case PIR::BaseType::Kind::Function: {
					// TODO:
					return std::string("[[FUNCTION]]");
				} break;

				default: EVO_FATAL_BREAK("Unknown base-type kind");
			};
		}();
		


		bool is_first_qualifer = true;
		for(const AST::Type::Qualifier& qualifier : type.qualifiers){
			if(type.qualifiers.size() > 1){
				if(is_first_qualifer){
					is_first_qualifer = false;
				}else{
					base_type_str += ' ';
				}
			}

			if(qualifier.isPtr){ base_type_str += '^'; }
			if(qualifier.isConst){ base_type_str += '|'; }
		}


		return base_type_str;
	};




	auto SourceManager::addEntry(Source::ID src_id, PIR::Func::ID func_id) noexcept -> void {
		evo::debugAssert(this->isLocked(), "Can only do add entry when locked");
		evo::debugAssert(this->hasEntry() == false, "Already has an entry function");

		this->entry.emplace(src_id, func_id);
	};


	auto SourceManager::getEntry() const noexcept -> Entry {
		evo::debugAssert(this->isLocked(), "Can only do add entry when locked");
		evo::debugAssert(this->hasEntry(), "SourceManager does not have an entry");

		return *this->entry;
	};





	auto SourceManager::getIntrinsics() const noexcept -> const std::vector<PIR::Intrinsic>& {
		evo::debugAssert(this->isLocked(), "Can only get intrinsics when locked");

		return this->intrinsics;
	};


	auto SourceManager::getIntrinsic(PIR::Intrinsic::ID id) const noexcept -> const PIR::Intrinsic& {
		evo::debugAssert(this->isLocked(), "Can only get intrinsics when locked");

		return this->intrinsics[id.id];
	};


	
};
