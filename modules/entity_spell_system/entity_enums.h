#ifndef ENTITY_ENUMS_H
#define ENTITY_ENUMS_H

/*************************************************************************/
/*  entity_enums.h                                                       */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "core/object/object.h"
#include "core/string/ustring.h"

class EntityEnums : public Object {
	GDCLASS(EntityEnums, Object);

public:
	static const String BINDING_STRING_ENTITY_PLAYER_TYPES;
	static const String BINDING_STRING_ENTITY_CONTOLLER;
	static const String BINDING_STRING_ENTITY_FLAGS;
	static const String BINDING_STRING_ENTITY_STATE_TYPES;
	static const String BINDING_STRING_COMMON_CHARCATER_SKELETON_POINTS;
	static const String BINDING_STRING_AI_STATES;
	static const String BINDING_STRING_PET_STATES;
	static const String BINDING_STRING_ENTITY_IMMUNITY_FLAGS;
	static const String BINDING_STRING_ENTITY_RELATION_TYPE;
	static const String BINDING_STRING_ENTITY_INTERACTION_TYPE;
	static const String BINDING_STRING_ENTITY_PLAYSTYLE_TYPE;
	static const String BINDING_STRING_ENTITY_WINDOWS;
	static const String BINDING_STRING_ENTITY_ENTITY_RESOURCE_INDICES;

	enum EntityPlayerType {
		ENTITY_PLAYER_TYPE_NONE,
		ENTITY_PLAYER_TYPE_PLAYER,
		ENTITY_PLAYER_TYPE_NETWORKED,
		ENTITY_PLAYER_TYPE_AI,
		ENTITY_PLAYER_TYPE_DISPLAY,
	};

	enum EntityController {
		ENITIY_CONTROLLER_NONE,
		ENITIY_CONTROLLER_PLAYER,
		ENITIY_CONTROLLER_AI
	};

	enum EntityFlags {
		ENITIY_FLAGS_NONE = 0,

		ENTITY_FLAGS_UNTARGETALBE = 1 << 0,
		ENTITY_FLAGS_HIDDEN = 1 << 1,
		ENTITY_FLAGS_INTERACTABLE = 1 << 2,
		ENTITY_FLAGS_HOSTILE = 1 << 3,
	};

	enum EntityStateTypeFlags {
		ENTITY_STATE_TYPE_FLAG_NONE = 0,
		ENTITY_STATE_TYPE_FLAG_STUN = 1 << 0,
		ENTITY_STATE_TYPE_FLAG_ROOT = 1 << 1,
		ENTITY_STATE_TYPE_FLAG_FROZEN = 1 << 2,
		ENTITY_STATE_TYPE_FLAG_SILENCED = 1 << 3,
		ENTITY_STATE_TYPE_FLAG_DISORIENTED = 1 << 4,
		ENTITY_STATE_TYPE_FLAG_FEARED = 1 << 5,
		ENTITY_STATE_TYPE_FLAG_BURNING = 1 << 6,
		ENTITY_STATE_TYPE_FLAG_COLD = 1 << 7,
		ENTITY_STATE_TYPE_FLAG_CURSED = 1 << 8,
		ENTITY_STATE_TYPE_FLAG_PACIFIED = 1 << 9,
	};

	enum EntityStateTypeIndexes {
		ENTITY_STATE_TYPE_INDEX_NONE = 0,
		ENTITY_STATE_TYPE_INDEX_STUN = 1,
		ENTITY_STATE_TYPE_INDEX_ROOT = 2,
		ENTITY_STATE_TYPE_INDEX_FROZEN = 3,
		ENTITY_STATE_TYPE_INDEX_SILENCED = 4,
		ENTITY_STATE_TYPE_INDEX_DISORIENTED = 5,
		ENTITY_STATE_TYPE_INDEX_FEARED = 6,
		ENTITY_STATE_TYPE_INDEX_BURNING = 7,
		ENTITY_STATE_TYPE_INDEX_COLD = 8,
		ENTITY_STATE_TYPE_INDEX_CURSED = 9,
		ENTITY_STATE_TYPE_INDEX_PACIFIED = 10,

		ENTITY_STATE_TYPE_INDEX_MAX = 11,
	};

	static EntityStateTypeFlags get_state_flag_for_index(int index) {
		switch (index) {
			case ENTITY_STATE_TYPE_INDEX_STUN:
				return ENTITY_STATE_TYPE_FLAG_STUN;
			case ENTITY_STATE_TYPE_INDEX_ROOT:
				return ENTITY_STATE_TYPE_FLAG_ROOT;
			case ENTITY_STATE_TYPE_INDEX_FROZEN:
				return ENTITY_STATE_TYPE_FLAG_FROZEN;
			case ENTITY_STATE_TYPE_INDEX_SILENCED:
				return ENTITY_STATE_TYPE_FLAG_SILENCED;
			case ENTITY_STATE_TYPE_INDEX_DISORIENTED:
				return ENTITY_STATE_TYPE_FLAG_DISORIENTED;
			case ENTITY_STATE_TYPE_INDEX_FEARED:
				return ENTITY_STATE_TYPE_FLAG_FEARED;
			case ENTITY_STATE_TYPE_INDEX_BURNING:
				return ENTITY_STATE_TYPE_FLAG_BURNING;
			case ENTITY_STATE_TYPE_INDEX_COLD:
				return ENTITY_STATE_TYPE_FLAG_COLD;
			case ENTITY_STATE_TYPE_INDEX_CURSED:
				return ENTITY_STATE_TYPE_FLAG_CURSED;
			case ENTITY_STATE_TYPE_INDEX_PACIFIED:
				return ENTITY_STATE_TYPE_FLAG_PACIFIED;
		}

		return ENTITY_STATE_TYPE_FLAG_NONE;
	}

	enum EntityImmunityFlags {
		ENTITY_IMMUNITY_FLAG_NONE = 0,

		ENTITY_IMMUNITY_FLAG_STUN = 1 << 0,
		ENTITY_IMMUNITY_FLAG_ROOT = 1 << 1,
		ENTITY_IMMUNITY_FLAG_FREEZE = 1 << 2,
		ENTITY_IMMUNITY_FLAG_SILENCE = 1 << 3,
		ENTITY_IMMUNITY_FLAG_DISORIENT = 1 << 4,
		ENTITY_IMMUNITY_FLAG_FEAR = 1 << 5,
		ENTITY_IMMUNITY_FLAG_BURNING = 1 << 6,
		ENTITY_IMMUNITY_FLAG_COLD = 1 << 7,
		ENTITY_IMMUNITY_FLAG_PACIFY = 1 << 8,

		ENTITY_IMMUNITY_FLAG_MAGIC = 1 << 9,
		ENTITY_IMMUNITY_FLAG_POISON = 1 << 10,
		ENTITY_IMMUNITY_FLAG_PHYSICAL = 1 << 11,
		ENTITY_IMMUNITY_FLAG_CURSE = 1 << 12,
		ENTITY_IMMUNITY_FLAG_BLEED = 1 << 13,

		ENTITY_IMMUNITY_FLAG_MELEE = 1 << 14,
		ENTITY_IMMUNITY_FLAG_HOLY = 1 << 15,
		ENTITY_IMMUNITY_FLAG_SHADOW = 1 << 16,
		ENTITY_IMMUNITY_FLAG_NATURE = 1 << 17,
		ENTITY_IMMUNITY_FLAG_FIRE = 1 << 18,
		ENTITY_IMMUNITY_FLAG_FROST = 1 << 19,
		ENTITY_IMMUNITY_FLAG_LIGHTNING = 1 << 20,
		ENTITY_IMMUNITY_FLAG_CHAOS = 1 << 21,

		ENTITY_IMMUNITY_FLAG_SLOW = 1 << 22,
		ENTITY_IMMUNITY_FLAG_CRIT = 1 << 23,
		ENTITY_IMMUNITY_FLAG_AOE = 1 << 24,
		ENTITY_IMMUNITY_FLAG_DAMAGE = 1 << 25,
		ENTITY_IMMUNITY_FLAG_FALL_DAMAGE = 1 << 26,
		ENTITY_IMMUNITY_FLAG_PROJECTILE = 1 << 27,
		ENTITY_IMMUNITY_FLAG_DEBUFF = 1 << 28,
		ENTITY_IMMUNITY_FLAG_ATTACKS = 1 << 29,
		ENTITY_IMMUNITY_FLAG_DISPELL = 1 << 30,
	};

	enum CommonCharacterSkeletonPoints {
		COMMON_SKELETON_POINT_ROOT = 0,
		COMMON_SKELETON_POINT_PELVIS,
		COMMON_SKELETON_POINT_SPINE,
		COMMON_SKELETON_POINT_SPINE_1,
		COMMON_SKELETON_POINT_SPINE_2,
		COMMON_SKELETON_POINT_NECK,
		COMMON_SKELETON_POINT_HEAD,
		COMMON_SKELETON_POINT_TORSO,
		COMMON_SKELETON_POINT_RIGHT_HIP,
		COMMON_SKELETON_POINT_LEFT_HIP,
		COMMON_SKELETON_POINT_BACK,
		COMMON_SKELETON_POINT_LEFT_HAND,
		COMMON_SKELETON_POINT_RIGHT_HAND,

		COMMON_SKELETON_POINT_WEAPON_LEFT,
		COMMON_SKELETON_POINT_WEAPON_RIGHT,
		COMMON_SKELETON_POINT_WEAPON_LEFT_BACK,
		COMMON_SKELETON_POINT_WEAPON_RIGHT_BACK,

		COMMON_SKELETON_POINT_WEAPON_LEFT_SHIELD,
		COMMON_SKELETON_POINT_WEAPON_RIGHT_SHIELD,

		COMMON_SKELETON_POINTS_MAX,
	};

	enum AIStates {
		AI_STATE_OFF = 0,
		AI_STATE_REST,
		AI_STATE_PATROL,
		AI_STATE_FOLLOW_PATH,
		AI_STATE_REGENERATE,
		AI_STATE_ATTACK,

		AI_STATE_PET_OFF,
		AI_STATE_PET_FOLLOW,
		AI_STATE_PET_STOP,
		AI_STATE_PET_ATTACK,

		AI_STATE_MAX,
	};

	enum EntityRelationType {
		ENTITY_RELATION_TYPE_NEUTRAL = 0,
		ENTITY_RELATION_TYPE_FRIENDLY,
		ENTITY_RELATION_TYPE_HOSTILE,
	};

	enum EntityInteractionType {
		ENITIY_INTERACTION_TYPE_NORMAL = 0,
		ENITIY_INTERACTION_TYPE_SPEAK,
		ENITIY_INTERACTION_TYPE_LOOT,
		ENITIY_INTERACTION_TYPE_USE,
		ENITIY_INTERACTION_TYPE_TRAIN,
		ENITIY_INTERACTION_TYPE_VENDOR,
		ENITIY_INTERACTION_TYPE_NONE,
	};

	enum EntityClassPlaystyleType {
		ENTITY_CLASS_PLAYSTYLE_TYPE_MELEE = 0,
		ENTITY_CLASS_PLAYSTYLE_TYPE_SPELL,
		ENTITY_CLASS_PLAYSTYLE_TYPE_HYBRID,
		ENTITY_CLASS_PLAYSTYLE_TYPE_NONE,
	};

	enum EntityWindows {
		ENTITY_WINDOW_LOOT = 0,
		ENTITY_WINDOW_CONTAINER,
		ENTITY_WINDOW_VENDOR,
		ENTITY_WINDOW_TRAINER,
	};

	enum EntityResourceIndices {
		ENTITY_RESOURCE_INDEX_HEALTH = 0,
		ENTITY_RESOURCE_INDEX_SPEED = 1,
		ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN = 2,
	};

	enum {
		BASE_XP = 50,
		ENTITY_INTERACT_RANGE = 4,
		ENTITY_INTERACT_RANGE_SQUARED = ENTITY_INTERACT_RANGE * ENTITY_INTERACT_RANGE,
	};

	EntityEnums() {}

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(EntityEnums::EntityPlayerType);
VARIANT_ENUM_CAST(EntityEnums::EntityController);
VARIANT_ENUM_CAST(EntityEnums::EntityFlags);
VARIANT_ENUM_CAST(EntityEnums::EntityStateTypeFlags);
VARIANT_ENUM_CAST(EntityEnums::EntityStateTypeIndexes);
VARIANT_ENUM_CAST(EntityEnums::CommonCharacterSkeletonPoints);
VARIANT_ENUM_CAST(EntityEnums::AIStates);
VARIANT_ENUM_CAST(EntityEnums::EntityImmunityFlags);
VARIANT_ENUM_CAST(EntityEnums::EntityRelationType);
VARIANT_ENUM_CAST(EntityEnums::EntityInteractionType);
VARIANT_ENUM_CAST(EntityEnums::EntityClassPlaystyleType);
VARIANT_ENUM_CAST(EntityEnums::EntityWindows);
VARIANT_ENUM_CAST(EntityEnums::EntityResourceIndices);

#endif
