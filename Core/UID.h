/*
#ifndef __CRYSTAL_CORE_UID_H__
#define __CRYSTAL_CORE_UID_H__

#include <bitset>

namespace Crystal {
	namespace Core {

class UID
{
public:
	enum class Type {
		Node,
		Edge,
		Face,
		Surface,
		Glyph,
		Joint,
		Bone,
	};

	UID(const int id, const char type)
	{
		this->id = id;
		this->type = type;
	}


	UID(const int id, const Type type)
	{
		this->id = id;
		this->type = char(type);
	}

	//toInt() const { return }

	std::bitset<32> get() const{
		std::bitset<32> result;
		for (int i = 0; i < 24; ++i) {
			result.set(i, id[i]);
		}
		for (int i = 0; i < 8; ++i) {
			result.set(i + 24, type[i]);
		}
		return result;
	}

	int getID() const { return id.to_ulong(); }

	Type getType() const { return Type(type.to_ulong()); }

	int toInt() const { return get().to_ulong(); }

private:
	std::bitset<24> id;
	std::bitset<8> type;
};
	}
}

#endif
*/