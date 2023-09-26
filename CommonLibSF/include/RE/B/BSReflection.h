#pragma once

namespace RE
{
	namespace BSReflection
	{
		namespace Metadata
		{

		}

		enum class AttributeUsage
		{
			kNone,
			kClass = 1 << 1,
			kProperty = 1 << 2,
			kEnum = 1 << 3,
			kEnumConstant = 1 << 4,
			kReleaseFinal = 1 << 5,

			kClassAndProperty = 6,
			kType = 14,
			kAll = 30
		};

		class __declspec(novtable) IStringConverter
		{
		public:
			SF_RTTI(BSReflection__IStringConverter);
		};

		class __declspec(novtable) IObject
		{
		public:
			SF_RTTI_VTABLE(BSReflection__IObject);

			virtual void Unk_00();  // 00
			virtual ~IObject();     // 01
		};

		struct TypedData;

		class __declspec(novtable) IType
		{
		public:
			SF_RTTI(BSReflection__IType);

			// add
			virtual TypedData*  GetZeroed(TypedData* a_dst, void* a_buf) = 0;
			virtual TypedData*  Copy(TypedData* a_dst, void* a_buf, TypedData* a_src) = 0;
			virtual TypedData*  Copy2(TypedData* a_dst, void* a_buf, TypedData* a_src) = 0;
			virtual void        Unk03() = 0;
			virtual const char* GetName() = 0;
		};
		static_assert(sizeof(IType) == 0x08);

		class IReferenceType : public IType
		{
		public:
			SF_RTTI(BSReflection__IReferenceType);
		};

		class IBorrowedPtrType : public IReferenceType
		{
		public:
			SF_RTTI(BSReflection__IBorrowedPtrType);
		};

		class ISharedPtrType : public IReferenceType
		{
		public:
			SF_RTTI(BSReflection__ISharedPtrType);
		};

		class IUniquePtrType : public IReferenceType
		{
		public:
			SF_RTTI(BSReflection__IReferenceType);
		};

		template <class T>
		class ReflectionBase
		{
		public:
			//members
			std::uint32_t size;   // 00
			std::uint16_t align;  // 04
			std::uint8_t  unk06;  // 06 - Type?
			std::uint8_t  unk07;  // 07 - Flags of some sort?
			void*         unk08;  // 08 - Pointer to a different Type???
		};
		static_assert(sizeof(ReflectionBase<ClassType>) == 0x10);

		class Any
		{
		public:

		};

		template <class Type, class AllowedTypes, class UNK>
		class TypeBase : public Type
		{
		public:
		};

		class alignas(0x10) AnyType : public TypeBase<IUniquePtrType, Any, std::true_type>
		{
		public:
			SF_RTTI(BSReflection__AnyType);

		};
		//static_assert(sizeof(AnyType) == 0x30);

		class BasicType : public IType
		{
		public:
			SF_RTTI_VTABLE(BSReflection__BasicType);

			// members
			std::uint32_t size;      // 08
			std::uint16_t align;     // 0C
			std::uint8_t  unk0E;     // 0E - 00
			std::uint8_t  unk0F;     // 0F - FF
			const char*   name;      // 10
			std::uint8_t  id;        // 18
			std::uint8_t  isSigned;  // 19
			std::uint16_t unk1A;     // 1A
			std::uint32_t unk1C;     // 1C
		};
		static_assert(sizeof(BasicType) == 0x20);

		class ClassType : public IType, public ReflectionBase<ClassType>
		{
		public:
			SF_RTTI_VTABLE(BSReflection__ClassType);

			struct Member
			{
			public:
				//members
				const char*   name;    // 00
				IType*        type;    // 08
				std::uint32_t offset;  // 10
				std::uint32_t unk14;   // 14
				std::uint64_t unk18;   // 18
				std::uint64_t unk20;   // 20
				std::uint64_t unk28;   // 28
				std::uint64_t unk30;   // 30
			};

			//members
			const char* name;       // 18
			void*       ctor0;      // 20
			void*       ctor1;      // 28
			void*       ctor2;      // 30
			void*       ctor3;      // 38
			Member*     members;    // 40 - Array of members
			std::byte   unk48[72];  // 48
		};
		static_assert(sizeof(ClassType) == 0x90);

		class EnumerationType : public IType, public ReflectionBase<EnumerationType>
		{
		public:
			SF_RTTI_VTABLE(BSReflection__EnumerationType);

			struct enumeration
			{
			public:
				const char*   name;   // 00
				std::uint64_t value;  // 08
			};

			//members
			const char*  name;    // 18
			enumeration* values;  // 20 - Array of values
			void*        unk28;   // 28 - Stop value for Array??? or pointer to next set of values???
			void*        unk30;   // 30 - Pointer to same value as above
		};
		static_assert(sizeof(EnumerationType) == 0x38);

		struct TypedData
		{
		public:
			// members
			IType* type;  // 00
			void*  data;  // 08
		};
		static_assert(sizeof(TypedData) == 0x10);
	}

	template <class T>
	class BasicTypeConverter : public BSReflection::IStringConverter
	{
	public:
	};

	class StringTypeConverter : public BSReflection::IStringConverter
	{
	public:
		SF_RTTI_VTABLE(__StringTypeConverter);
	};

	class EnumStringConverter : public BSReflection::IStringConverter
	{
	public:
		SF_RTTI_VTABLE(__EnumStringConverter);
	};

	class ClassStringConverter : public BSReflection::IStringConverter
	{
	public:
		SF_RTTI_VTABLE(__ClassStringConverter);
	};

	class CollectionStringConverter : public BSReflection::IStringConverter
	{
	public:
		SF_RTTI_VTABLE(__CollectionStringConverter);
	};

	class ReferenceStringConverter : public BSReflection::IStringConverter
	{
	public:
		SF_RTTI_VTABLE(__ReferenceStringConverter);
	};
}
