#pragma once


#include <Evo.h>


#include "Source.h"
#include "PIR.h"
#include "Message.h"

#include <functional>
#include <filesystem>
#include <unordered_set>

namespace panther{


	class SourceManager{
		public:
			using MessageCallback = std::function<void(const Message&)>;

			struct Entry{
				Source::ID src_id;
				PIR::Func::ID func_id;
			};

			struct Config{
				std::string basePath;
			};

			enum class GetSourceIDError{
				EmptyPath,
				SameAsCaller,
				NotOneOfSources,
				DoesntExist,
			};

		public:

			SourceManager(Config&& config_data, MessageCallback msg_callback) : config(std::move(config_data)), message_callback(msg_callback) {};
			~SourceManager() = default;


			EVO_NODISCARD inline auto numSources() const noexcept -> size_t { return this->sources.size(); };
			EVO_NODISCARD inline auto getConfig() const noexcept -> const Config& { return this->config; };


			// The purpose of locking is to make sure no sources are added after doing things like tokenizing
			// 	this is to ensure that pointers/references still point to the right place

			EVO_NODISCARD inline auto lock() noexcept -> void {
				evo::debugAssert(this->is_locked == false, "SourceManager is already locked");

				this->is_locked = true;
			};

			EVO_NODISCARD inline auto isLocked() const noexcept -> bool { return this->is_locked; };


			//////////////////////////////////////////////////////////////////////
			// funcs that require it is unlocked

			// TODO: other permutations of refs
			EVO_NODISCARD auto addSource(std::filesystem::path&& location, std::string&& data, const Source::Config& src_config) noexcept -> Source::ID;



			//////////////////////////////////////////////////////////////////////
			// funcs that require it to be locked


			EVO_NODISCARD auto emitMessage(const Message& msg) const noexcept -> void;


			// EVO_NODISCARD auto getSource(Source::ID id)       noexcept ->       Source&;
			EVO_NODISCARD auto getSource(Source::ID id) const noexcept -> const Source&;

			// file_location is the file that has the @import(), and src_path is the value inside the @import()
			EVO_NODISCARD auto getSourceID(const std::filesystem::path& file_location, std::string_view src_path) const noexcept
				-> evo::Expected<Source::ID, GetSourceIDError>;

			EVO_NODISCARD auto getSources() noexcept -> std::vector<Source>&;
			EVO_NODISCARD auto getSources() const noexcept -> const std::vector<Source>&;



			// returns number of sources taht failed tokenizing
			EVO_NODISCARD auto tokenize() noexcept -> evo::uint;

			// returns number of sources taht failed parsing
			EVO_NODISCARD auto parse() noexcept -> evo::uint;

			auto initBuiltinTypes() noexcept -> void;
			auto initIntrinsics() noexcept -> void;

			// returns number of sources taht failed parsing
			EVO_NODISCARD auto semanticAnalysis() noexcept -> evo::uint;





			///////////////////////////////////
			// objects

			// If an equivalent type already exists, return its ID instead
			struct GottenBaseTypeID{
				PIR::BaseType::ID id;
				bool created;
			};
			EVO_NODISCARD auto getOrCreateBaseType(PIR::BaseType&& base_type) noexcept -> GottenBaseTypeID;

			EVO_NODISCARD inline auto getBaseType(PIR::BaseType::ID id) const noexcept -> const PIR::BaseType& { return this->base_types[id.id]; };
			EVO_NODISCARD inline auto getBaseType(PIR::BaseType::ID id)       noexcept ->       PIR::BaseType& { return this->base_types[id.id]; };
			EVO_NODISCARD auto getBaseType(Token::Kind tok_kind) noexcept -> PIR::BaseType&;
			EVO_NODISCARD auto getBaseTypeID(Token::Kind tok_kind) const noexcept -> PIR::BaseType::ID;


			// gets type with matching ID
			// if type doesn't already exist, create a new one
			// The returned bool is if a new one is created
			// TODO: &&
			struct GottenTypeID{
				PIR::Type::ID id;
				bool created;
			};
			EVO_NODISCARD auto getOrCreateTypeID(const PIR::Type& type) noexcept -> GottenTypeID;

			// gets type with matching ID
			// TODO: &&
			EVO_NODISCARD auto getTypeID(const PIR::Type& type) const noexcept -> PIR::Type::ID;

			EVO_NODISCARD static inline auto getDummyTypeID() noexcept -> PIR::Type::ID { return PIR::Type::ID(std::numeric_limits<uint32_t>::max()); };


			EVO_NODISCARD inline auto getType(PIR::Type::ID id) const noexcept -> const PIR::Type& {
				return this->types[id.id];
			};

			// TODO: better way of doing this?
			EVO_NODISCARD static inline auto getTypeImport() noexcept -> PIR::Type::ID { return PIR::Type::ID(0); };
			EVO_NODISCARD static inline auto getTypeInt() noexcept -> PIR::Type::ID { return PIR::Type::ID(1); };
			EVO_NODISCARD static inline auto getTypeUInt() noexcept -> PIR::Type::ID { return PIR::Type::ID(2); };
			EVO_NODISCARD static inline auto getTypeBool() noexcept -> PIR::Type::ID { return PIR::Type::ID(3); };
			EVO_NODISCARD static inline auto getTypeString() noexcept -> PIR::Type::ID { return PIR::Type::ID(4); };
			EVO_NODISCARD static inline auto getTypeISize() noexcept -> PIR::Type::ID { return PIR::Type::ID(5); };
			EVO_NODISCARD static inline auto getTypeUSize() noexcept -> PIR::Type::ID { return PIR::Type::ID(6); };


			EVO_NODISCARD auto printType(PIR::Type::VoidableID id) const noexcept -> std::string;
			EVO_NODISCARD auto printType(PIR::Type::ID id) const noexcept -> std::string;


			EVO_NODISCARD auto addEntry(Source::ID src_id, PIR::Func::ID func_id) noexcept -> void;

			EVO_NODISCARD inline auto hasEntry() const noexcept -> bool { return this->entry.has_value(); };
			EVO_NODISCARD auto getEntry() const noexcept -> Entry;


			EVO_NODISCARD auto hasExport(std::string_view ident) const noexcept -> bool;
			auto addExport(std::string_view ident) noexcept -> void;


			EVO_NODISCARD auto getIntrinsics() const noexcept -> evo::ArrayProxy<PIR::Intrinsic>;
			EVO_NODISCARD auto getIntrinsic(PIR::Intrinsic::ID id) const noexcept -> const PIR::Intrinsic&;
			EVO_NODISCARD auto getIntrinsic(PIR::Intrinsic::Kind kind) const noexcept -> const PIR::Intrinsic&;
			EVO_NODISCARD static inline auto getIntrinsicID(PIR::Intrinsic::Kind kind) noexcept -> PIR::Intrinsic::ID {
				return PIR::Intrinsic::ID(static_cast<uint32_t>(kind));
			};

		private:
			Config config;

			std::vector<Source> sources{};
			bool is_locked = false;

			std::vector<PIR::BaseType> base_types{};
			std::vector<PIR::Type> types{};

			std::optional<Entry> entry{};

			evo::StaticVector<PIR::Intrinsic, static_cast<size_t>(PIR::Intrinsic::Kind::_MAX_)> intrinsics{};
			
			std::unordered_set<std::string_view> exported_funcs{};


			MessageCallback message_callback;

	};


};