#include "cheats.h"
#include "offset.h"

r_hmodue gtav_cheats::get_mod_addr(const r_wchar* str)
{
	r_hmodue mods[0xff]{ 0 };
	r_dword size = 0;

	if (K32EnumProcessModulesEx(m_proc, mods, sizeof(mods), &size, LIST_MODULES_64BIT))
	{
		for (auto i = 0; i < size / sizeof(r_hmodue); i++)
		{
			r_wchar buffer[1024]{ 0 };
			if (K32GetModuleFileNameExW(m_proc, mods[i], buffer, sizeof(buffer) / sizeof(r_wchar)))
			{
				std::wstring temp = buffer;
				if (temp.find(str) != std::wstring::npos) return mods[i];
			}
		}
	}

	return 0;
}

void gtav_cheats::update_addrs()
{
	m_dwpWorldBase = 0;
	m_dwpTunableBase = 0;
	m_dwpGlobalBase = 0;

	m_dwpReplayInterfaceBase = 0;
	m_Replay_dwpPedInterface = 0;
	m_Replay_dwpPedList = 0;

	m_dwpPlayerBase = 0;
	m_Player_dwpPosBase = 0;
	m_Player_dwpPlayerInfo = 0;
	m_Player_dwpAttackerBase = 0;

	m_dwpVehicleBase = 0;
	m_Vehicle_dwpPosBase = 0;
	m_Vehicle_dwpHandling = 0;

	m_dwpWeaponBase = 0;
	m_dwpWeaponManager = 0;
	m_dwpWeaponCur = 0;
	m_dwpAmmoInfo = 0;

	m_dwpWorldBase = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_WORLD);
	m_dwpTunableBase = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_TUNABLE);
	m_dwpGlobalBase = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL);
	m_dwpReplayInterfaceBase = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_REPLAY_INTERFACE);

	if (m_dwpReplayInterfaceBase)
	{
		m_Replay_dwpPedInterface = read<r_dword_ptr>(m_dwpReplayInterfaceBase + OFFSET_REPLAY_PED_INTERFACE);
		if (m_Replay_dwpPedInterface)
		{
			m_Replay_dwpPedList = read<r_dword_ptr>(m_Replay_dwpPedInterface + OFFSET_PED_INTERFACE_PED_LIST);
		}
	}

	if (m_dwpWorldBase)
	{
		m_dwpPlayerBase = read<r_dword_ptr>(m_dwpWorldBase + OFFSET_PLAYER);
		if (m_dwpPlayerBase)
		{
			m_Player_dwpPosBase = read<r_dword_ptr>(m_dwpPlayerBase + OFFSET_ENTITY_POSBASE);
			m_Player_dwpPlayerInfo = read<r_dword_ptr>(m_dwpPlayerBase + OFFSET_PLAYER_INFO);
			m_Player_dwpAttackerBase = read<r_dword_ptr>(m_dwpPlayerBase + OFFSET_ENTITY_ATTACKER);
			m_dwpVehicleBase = read<r_dword_ptr>(m_dwpPlayerBase + OFFSET_PLAYER_VEHICLE);
			if (m_dwpVehicleBase)
			{
				m_Vehicle_dwpPosBase = read<r_dword_ptr>(m_dwpVehicleBase + OFFSET_ENTITY_POSBASE);
				m_Vehicle_dwpHandling = read<r_dword_ptr>(m_dwpVehicleBase + OFFSET_VEHICLE_HANDLING);
			}
		}
	}

	m_dwpWeaponBase = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_WEAPON);
	if (m_dwpPlayerBase)
	{
		m_dwpWeaponManager = read<r_dword_ptr>(m_dwpPlayerBase + OFFSET_WEAPON_MANAGER);
		if (m_dwpWeaponManager)
		{
			m_dwpWeaponCur = read<r_dword_ptr>(m_dwpWeaponManager + OFFSET_WEAPON_CURRENT);
			if (m_dwpWeaponCur)
			{
				m_dwpAmmoInfo = read<r_dword_ptr>(m_dwpWeaponCur + OFFSET_WEAPON_AMMOINFO);
			}
		}
	}
}

void gtav_cheats::show_menu()
{
	if (m_show)
	{
		system("cls");
		m_show = false;

		cmd_color(m_state_unlimited_endurance, "[ALT] + [0] \t 无限耐力");
		cmd_color(m_state_npc_ignore_player, "[ALT] + [1] \t NPC忽略玩家");
		cmd_color(m_state_player_god_mode, "[ALT] + [2] \t 玩家上帝模式");
		cmd_color(m_state_never_fall, "[ALT] + [3] \t 永不摔倒");
		cmd_color(m_state_fake_dead_hide, "[ALT] + [4] \t 假死雷达隐藏");
		cmd_color(m_state_vehicle_god_mode, "[ALT] + [5] \t 车辆上帝模式");
		cmd_color(m_state_infinite_jet, "[ALT] + [6] \t 无限喷射");
		cmd_color(m_state_super_weapon_damage, "[ALT] + [7] \t 武器超级伤害");
		cmd_color(m_state_unlimited_ammo, "[ALT] + [8] \t 无限弹药");
		cmd_color(m_state_space_based_gun_without_cooling, "[ALT] + [9] \t 天基炮无冷却");
		cmd_color(m_state_unlock_bunker_research, "[ALT] + [+] \t 解锁地堡研究");
		cmd_color(m_state_anti_AFK_kick_out, "[ALT] + [-] \t 反AFK踢出战局");
		cmd_color(m_state_money_bag, "[ALT] + [/] \t 钱袋刷钱");
		cmd_color(m_state_no_reload, "[ALT] + [*] \t 无需换弹");

		std::cout << std::endl;

		std::cout << "[CTRL] + [0] \t 生成MK2" << std::endl;
		std::cout << "[CTRL] + [1] \t 生成骷髅马" << std::endl;
		std::cout << "[CTRL] + [2] \t 生成德罗索" << std::endl;
		std::cout << "[CTRL] + [3] \t 生成义警" << std::endl;
		std::cout << "[CTRL] + [4] \t 生成P-996" << std::endl;
		std::cout << "[CTRL] + [5] \t 生成九头蛇" << std::endl;
		std::cout << "[CTRL] + [6] \t 生成秃鹰" << std::endl;
		std::cout << "[CTRL] + [7] \t 生成游艇" << std::endl;

		std::cout << std::endl;

		std::cout << "[TAB] + [0] \t 角色属性全满" << std::endl;
		std::cout << "[TAB] + [1] \t 零食防弹衣全满" << std::endl;
		std::cout << "[TAB] + [2] \t 解锁改车配件" << std::endl;
		std::cout << "[TAB] + [3] \t 解锁武器涂装" << std::endl;
		std::cout << "[TAB] + [4] \t 解锁批发价" << std::endl;
		std::cout << "[TAB] + [5] \t 解锁奖章" << std::endl;
		std::cout << "[TAB] + [6] \t 解锁衣服" << std::endl;

		std::cout << std::endl;

		std::cout << "[CAPSLK] + [0] \t 潜行匿踪" << std::endl;
		std::cout << "[CAPSLK] + [1] \t 兵不厌诈" << std::endl;
		std::cout << "[CAPSLK] + [2] \t 气势汹汹" << std::endl;
		std::cout << "[CAPSLK] + [3] \t 离开线上" << std::endl;
		std::cout << "[CAPSLK] + [4] \t 进入线上" << std::endl;
		std::cout << "[CAPSLK] + [5] \t 自杀" << std::endl;

		std::cout << std::endl;

		std::cout << "[F5] \t 传送到目标点" << std::endl;
		std::cout << "[F6] \t 传送到任务点" << std::endl;
		std::cout << "[F7] \t 取消通缉等级" << std::endl;
		std::cout << "[F8] \t 坐进个人载具" << std::endl;
	}
}

vector_2 gtav_cheats::get_target_point()
{
	vector_2 result{ 0 };
	r_dword_ptr addr = (r_dword_ptr)m_mod + ADDRESS_BLIP;
	for (int i = 2000; i > 1; i--)
	{
		r_dword64 index = read<r_dword64>(addr + (i * 8));
		if (index)
		{
			r_dword buf1 = read<r_dword>((r_dword_ptr)index + 0x40);
			r_dword buf2 = read<r_dword>((r_dword_ptr)index + 0x48);
			if (index > 0 && buf1 == 8 && buf2 == 84)
			{
				result = read<vector_2>((r_dword_ptr)index + 0x10);
				break;
			}
		}
	}
	return result;
}

vector_3 gtav_cheats::get_aim_point()
{
	vector_3 result{ 0 };
	r_dword_ptr addr = (r_dword_ptr)m_mod + ADDRESS_BLIP;
	for (int i = 2000; i > 1; i--)
	{
		r_dword64 index = read<r_dword64>(addr + (i * 8));
		if (index)
		{
			r_dword buf1 = read<r_dword>((r_dword_ptr)index + 0x40);
			r_dword buf2 = read<r_dword>((r_dword_ptr)index + 0x48);
			if (index > 0 && buf1 == 1 && (buf2 == 5 || buf2 == 60 || buf2 == 66))
			{
				result = read<vector_3>((r_dword_ptr)index + 0x10);
				break;
			}
		}
	}
	return result;
}

void gtav_cheats::start_move(vector_3 dest)
{
	if (m_dwpPlayerBase)
	{
		r_byte res = read<r_byte>(m_dwpPlayerBase + OFFSET_PLAYER_INVEHICLE);
		if (!((res >> 4) & 1))//在车上
		{
			if (m_Vehicle_dwpPosBase) write<vector_3>(m_Vehicle_dwpPosBase + OFFSET_ENTITY_POSBASE_POS, dest);
			if (m_dwpVehicleBase) write<vector_3>(m_dwpVehicleBase + OFFSET_ENTITY_POS, dest);
		}
		else
		{
			if (m_Player_dwpPosBase) write<vector_3>(m_Player_dwpPosBase + OFFSET_ENTITY_POSBASE_POS, dest);
			if (m_dwpPlayerBase) write<vector_3>(m_dwpPlayerBase + OFFSET_ENTITY_POS, dest);
		}
	}
}

void gtav_cheats::move_to_target()
{
	vector_2 res = get_target_point();
	if (res.x == 64000.f && res.y == 64000.f) return;

	vector_3 dest{ res.x,res.y,-255.f };
	start_move(dest);
}

void gtav_cheats::move_to_aim()
{
	vector_3 res = get_aim_point();
	if (res.x == 64000.f && res.y == 64000.f && res.z == 64000.f) return;

	res.z += 1.0f;
	start_move(res);
}

void gtav_cheats::clear_wanted()
{
	if (m_Player_dwpPlayerInfo)
	{
		r_dword res = read<r_dword>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_WANTED);
		if (res > 0) write<r_dword>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_WANTED, 0);
	}
}

void gtav_cheats::kill_self()
{
	if (m_dwpPlayerBase)
	{
		write<float>(m_dwpPlayerBase + OFFSET_ENTITY_HEALTH, 0.f);
		write<float>(m_dwpPlayerBase + OFFSET_PLAYER_ARMOR, 0.f);
	}
}

void gtav_cheats::sit_in_personal_vehicle()
{
	auto func = [&](int val) -> r_dword_ptr
	{
		r_dword_ptr res = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL + 8 * ((val >> 0x12) & 0x3F));
		return 8 * (val & 0x3FFFF) + res;
	};

	r_dword_ptr m_dwpIntoPersonalVehicle = func(2409287 + 8);
	if (m_dwpIntoPersonalVehicle)
	{
		write<int>(m_dwpIntoPersonalVehicle, 1);
		Sleep(1000);
		if (read<int>(m_dwpIntoPersonalVehicle))
		{
			write<int>(m_dwpIntoPersonalVehicle, 0);
		}
	}
}

void gtav_cheats::unlimited_endurance(bool state)
{
	if (m_Player_dwpPlayerInfo)
	{
		values res = read<values>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_STAMINA);
		if (state && res._cur < res._max) write<float>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_STAMINA, res._max);
	}
}

void gtav_cheats::npc_ignore_player(bool state)
{
	if (m_Player_dwpPlayerInfo)
	{
		r_dword res = read<r_dword>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_NPC_IGNORE);
		if (state && res != 0x450000) write<r_dword>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_NPC_IGNORE, 0x450000);
		else if (state == false && res == 0x450000) write<r_dword>(m_Player_dwpPlayerInfo + OFFSET_PLAYER_INFO_NPC_IGNORE, 0);
	}
}

void gtav_cheats::player_god_mode(bool state)
{
	if (m_dwpPlayerBase)
	{
		r_byte res = read<r_byte>(m_dwpPlayerBase + OFFSET_ENTITY_GOD);
		if (state && res != 1) write<r_byte>(m_dwpPlayerBase + OFFSET_ENTITY_GOD, 1);
		else if (state == false && res == 1) write<r_byte>(m_dwpPlayerBase + OFFSET_ENTITY_GOD, 0);
	}
}

void gtav_cheats::never_fall(bool state)
{
	if (m_dwpPlayerBase)
	{
		r_byte res = read<r_byte>(m_dwpPlayerBase + OFFSET_PLAYER_RAGDOLL);
		if (state && res & 0x20) write<r_byte>(m_dwpPlayerBase + OFFSET_PLAYER_RAGDOLL, res ^ 0x20);
	}
}

void gtav_cheats::fake_dead_hide(bool state)
{
	if (m_dwpPlayerBase)
	{
		float res = read<float>(m_dwpPlayerBase + OFFSET_ENTITY_HEALTH_MAX);
		if (state && res > 0.f) write<float>(m_dwpPlayerBase + OFFSET_ENTITY_HEALTH_MAX, 0.f);
	}
}

void gtav_cheats::vehicle_god_mode(bool state)
{
	if (m_dwpVehicleBase)
	{
		r_byte res = read<r_byte>(m_dwpVehicleBase + OFFSET_ENTITY_GOD);
		if (state && res != 1) write<r_byte>(m_dwpVehicleBase + OFFSET_ENTITY_GOD, 1);
		else if (res == false && res != 0) write<r_byte>(m_dwpVehicleBase + OFFSET_ENTITY_GOD, 0);
	}
}

void gtav_cheats::infinite_jet(bool state)
{
	if (m_dwpVehicleBase)
	{
		float res = read<float>(m_dwpVehicleBase + OFFSET_VEHICLE_BOOST);
		if (state && res != 1.25f) write<float>(m_dwpVehicleBase + OFFSET_VEHICLE_BOOST, 1.25f);
	}
}

void gtav_cheats::super_weapon_damage(bool state)
{
	if (m_dwpWeaponCur)
	{
		static float max_value = 1000000.0f;
		float res = read<float>(m_dwpWeaponCur + OFFSET_WEAPON_BULLET_DMG);
		if (state && res != max_value) write<float>(m_dwpWeaponCur + OFFSET_WEAPON_BULLET_DMG, max_value);
	}
}

void gtav_cheats::no_reload(bool state)
{
	struct buffer { unsigned char data[3]; };
	if (state)
	{
		buffer temp{ 0x90, 0x90, 0x90 };
		write<buffer>((DWORD_PTR)m_mod + ADDRESS_MAGAZINE, temp);
	}
	else
	{
		buffer temp{ 0x41, 0x2B, 0xC9 };
		write<buffer>((DWORD_PTR)m_mod + ADDRESS_MAGAZINE, temp);
	}
}

void gtav_cheats::unlimited_ammo(bool state)
{
	r_byte res = read<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO);
	if (state && res != 0x90)
	{
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (0 * sizeof(r_byte)), 0x90);
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (1 * sizeof(r_byte)), 0x90);
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (2 * sizeof(r_byte)), 0x90);
	}
	else if (state == false && res != 0x41)
	{
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (0 * sizeof(r_byte)), 0x41);
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (1 * sizeof(r_byte)), 0x2b);
		write<r_byte>((r_dword_ptr)m_mod + ADDRESS_AMMO + (2 * sizeof(r_byte)), 0xd1);
	}
}

void gtav_cheats::space_based_gun_without_cooling(bool state)
{
	if (m_dwpTunableBase)
	{
		r_dword res = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ORBITAL_CANNON_COOLDOWN);
		if (state && res != 0) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ORBITAL_CANNON_COOLDOWN, 0);
	}
}

void gtav_cheats::unlock_bunker_research(bool state)
{
	if (m_dwpTunableBase)
	{
		r_dword res = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_BUNKER_RESEARCH);
		if (state && res != 1) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_BUNKER_RESEARCH, 1);
	}
}

void gtav_cheats::anti_AFK_kick_out(bool state)
{
	if (m_dwpTunableBase)
	{
		r_dword a = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK1);
		r_dword b = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK2);
		r_dword c = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK3);
		r_dword d = read<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK4);

		if (a != 2000000000) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK1, 2000000000);
		if (b != 2000000000) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK2, 2000000000);
		if (c != 2000000000) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK3, 2000000000);
		if (d != 2000000000) write<r_dword>(m_dwpTunableBase + OFFSET_TUNABLE_ANTI_IDLE_KICK4, 2000000000);
	}
}

void gtav_cheats::money_bag(bool state)
{
	static r_dword last_time = GetTickCount();
	r_dword cur_time = GetTickCount();
	if (cur_time - last_time < 10000) return;
	else last_time = cur_time;

	auto func = [&](int val) -> r_dword_ptr
	{
		r_dword_ptr res = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL + 8 * ((val >> 0x12) & 0x3F));
		return 8 * (val & 0x3FFFF) + res;
	};

	if (state && m_dwpPlayerBase)
	{
		r_dword_ptr m_dwpMoneyObject = func(2513253);
		r_dword_ptr m_dwpMoneyVal = func(2513247 + 1);
		r_dword_ptr m_dwpMoneyPosX = func(2513247 + 3);
		r_dword_ptr m_dwpMoneyPosY = func(2513247 + 4);
		r_dword_ptr m_dwpMoneyPosZ = func(2513247 + 5);
		state = m_dwpMoneyObject && m_dwpMoneyVal
			&& m_dwpMoneyPosX && m_dwpMoneyPosY && m_dwpMoneyPosZ;

		if (state)
		{
			vector_3 res = read<vector_3>(m_dwpPlayerBase + 0x90);

			write<r_byte>(m_dwpMoneyObject, 1);
			write<int>(m_dwpMoneyVal, 2000);

			write<float>(m_dwpMoneyPosX, res.x);
			write<float>(m_dwpMoneyPosY, res.y);
			write<float>(m_dwpMoneyPosZ, res.z + 5.0f);

			float buffer = read<float>(func(2513247));
			r_dword_ptr m_dwpMoneyCall = func(85 * (r_dword)buffer + 4263954 + 69);
			write<r_byte>(m_dwpMoneyCall, 2);
		}
	}
}

void gtav_cheats::handle_queue()
{
	const auto size = m_queue.size();
	if (size == 0) return;

	auto func = [&](int val) -> r_dword_ptr
	{
		r_dword_ptr res = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL + 8 * ((val >> 0x12) & 0x3F));
		return 8 * (val & 0x3FFFF) + res;
	};

	r_dword_ptr m_dwpStatCall = func(1377170);
	r_dword_ptr m_dwpStatHash = func(1387876);
	r_dword_ptr m_dwpStatValue = func(939452);
	bool state = m_dwpStatCall && m_dwpStatHash && m_dwpStatValue;

	if (state)
	{
		m_dwpStatCall += 0x2398;
		m_dwpStatHash += 0x20;
		m_dwpStatValue += 0xACB0;

		system("cls");
		std::cout << std::endl << std::endl << "正在处理 -> " << std::endl;

		for (int i = 0; i < size; i++)
		{
			unsigned int _hash = read<unsigned int>(m_dwpStatHash);
			int _value = read<int>(m_dwpStatValue);

			auto it = m_queue[i];
			write<unsigned int>(m_dwpStatHash, it._hash);
			write<int>(m_dwpStatValue, it._value);
			write<int>(m_dwpStatCall, -1);

			std::cout << "总数 : " << size << "\t 完成 : " << i << std::endl;
			Sleep(8000);

			write<unsigned int>(m_dwpStatHash, _hash);
			write<int>(m_dwpStatValue, _value);
		}
		m_queue.clear();
		m_show = true;
	}
}

void gtav_cheats::battle_handle(int tip)
{
	auto func = [&](int val) -> r_dword_ptr
	{
		r_dword_ptr res = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL + 8 * ((val >> 0x12) & 0x3F));
		return 8 * (val & 0x3FFFF) + res;
	};

	r_dword_ptr m_dwpSessionID = func(1312836);
	r_dword_ptr m_dwpSessionTransition = func(1312425);
	bool state = m_dwpSessionID && m_dwpSessionTransition;

	if (state)
	{
		write<int>(m_dwpSessionID, tip);
		write<int>(m_dwpSessionTransition, 1);
		Sleep(1000);
		write<int>(m_dwpSessionTransition, 0);
	}
}

void gtav_cheats::generate_vehicle(unsigned int val, float pos)
{
	auto func = [&](int val) -> r_dword_ptr
	{
		r_dword_ptr res = read<r_dword_ptr>((r_dword_ptr)m_mod + ADDRESS_GLOBAL + 8 * ((val >> 0x12) & 0x3F));
		return 8 * (val & 0x3FFFF) + res;
	};

	r_dword_ptr m_dwpVehicleSpawn1 = func(OFFSET_GLOBAL_VEHICLE_HASH + 2);
	r_dword_ptr m_dwpVehicleSpawn2 = func(OFFSET_GLOBAL_VEHICLE_HASH + 5);
	r_dword_ptr m_dwpVehicleHash = func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 66);
	r_dword_ptr m_dwpVehicleKickPrevent1 = func(OFFSET_GLOBAL_VEHICLE_HASH + 121);
	r_dword_ptr m_dwpVehicleKickPrevent2 = func(OFFSET_GLOBAL_VEHICLE_HASH + 122);
	r_dword_ptr m_dwpVehicleX = func(OFFSET_GLOBAL_VEHICLE_HASH + 7 + 0);
	r_dword_ptr m_dwpVehicleY = func(OFFSET_GLOBAL_VEHICLE_HASH + 7 + 1);
	r_dword_ptr m_dwpVehicleZ = func(OFFSET_GLOBAL_VEHICLE_HASH + 7 + 2);
	r_dword_ptr m_dwpPrimaryColor = func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 5);
	r_dword_ptr m_dwpSecondaryColor = func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 6);
	bool state = m_dwpVehicleSpawn1 && m_dwpVehicleSpawn2 && m_dwpVehicleHash
		&& m_dwpVehicleKickPrevent1 && m_dwpVehicleKickPrevent2
		&& m_dwpVehicleX && m_dwpVehicleY && m_dwpVehicleZ
		&& m_dwpPrimaryColor && m_dwpSecondaryColor;

	if (state)
	{
		vector_3 res = read<vector_3>(m_dwpPlayerBase + 0x90);
		float _cos = read<float>(m_Player_dwpPosBase + 0x20);
		float _sin = read<float>(m_Player_dwpPosBase + 0x30);
		res.x += pos * _sin;
		res.y += pos * _cos;

		write<unsigned int>(m_dwpVehicleHash, val);
		write<int>(m_dwpVehicleKickPrevent1, 2);

		write<int>(m_dwpVehicleKickPrevent2, 14);
		write<r_byte>(m_dwpSecondaryColor, -1);
		write<r_byte>(m_dwpPrimaryColor, -1);

		write<float>(m_dwpVehicleX, res.x);
		write<float>(m_dwpVehicleY, res.y);
		write<float>(m_dwpVehicleZ, -255.0f);

		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 10), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 11), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 12), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 13), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 14), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 15), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 16), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 17), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 18), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 19), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 20), 1);

		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 21), 4);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 22), 3);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 23), 3);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 24), 57);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 25), 4);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 26), 5);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 28), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 30), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 32), 1);
		write<r_byte>(func(OFFSET_GLOBAL_VEHICLE_HASH + 27 + 65), 1);

		write<int>(func(2459034 + 27 + 77), 0xF0400200);

		write<int>(m_dwpVehicleSpawn2, 1);
		write<int>(m_dwpVehicleSpawn1, 1);
	}
}

void gtav_cheats::full_character_attributes()
{
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_STAM"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_SHO"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_STRN"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_STL"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_FLY"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_DRIV"), 100);
	dStatPushBack(string_to_hash("SCRIPT_INCREASE_LUNG"), 100);
}

void gtav_cheats::full_body_snacks()
{
	dStatPushBack(string_to_hash("NO_BOUGHT_YUM_SNACKS"), 30);
	dStatPushBack(string_to_hash("NO_BOUGHT_HEALTH_SNACKS"), 15);
	dStatPushBack(string_to_hash("NO_BOUGHT_EPIC_SNACKS"), 5);
	dStatPushBack(string_to_hash("NUMBER_OF_ORANGE_BOUGHT"), 10);
	dStatPushBack(string_to_hash("MP_CHAR_ARMOUR_5_COUNT"), 10);
}

void gtav_cheats::unlock_car_accessories()
{
	dStatPushBack(string_to_hash("RACES_WON"), 50);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_1_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_2_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_3_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_4_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_5_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_6_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CARMOD_7_UNLCK"), -1);
	dStatPushBack(string_to_hash("NUMBER_SLIPSTREAMS_IN_RACE"), 110);
	dStatPushBack(string_to_hash("NUMBER_TURBO_STARTS_IN_RACE"), 90);
	dStatPushBack(string_to_hash("USJS_FOUND"), 50);
	dStatPushBack(string_to_hash("USJS_COMPLETED"), 50);
	dStatPushBack(string_to_hash("TIMES_RACE_BEST_LAP", "MPPLY_"), 101);
	dStatPushBack(string_to_hash("AWD_FMRALLYWONDRIVE"), 2);
	dStatPushBack(string_to_hash("AWD_FMWINSEARACE"), 2);
	dStatPushBack(string_to_hash("AWD_FMWINAIRRACE"), 2);
	dStatPushBack(string_to_hash("AWD_FM_RACES_FASTEST_LAP"), 101);
}

void gtav_cheats::unlock_weapon_paint()
{
	dStatPushBack(string_to_hash("PISTOL_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("CMBTPISTOL_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("PISTOL50_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("APPISTOL_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("MICROSMG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("SMG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("ASLTSMG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("ASLTRIFLE_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("CRBNRIFLE_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("ADVRIFLE_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("MG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("CMBTMG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("ASLTMG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("PUMP_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("SAWNOFF_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("BULLPUP_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("ASLTSHTGN_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("SNIPERRFL_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("HVYSNIPER_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("GRNLAUNCH_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("RPG_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("MINIGUNS_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("GRENADE_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("SMKGRENADE_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("STKYBMB_ENEMY_KILLS"), 600);
	dStatPushBack(string_to_hash("MOLOTOV_ENEMY_KILLS"), 600);
}

void gtav_cheats::unlock_wholesale_price()
{
	dStatPushBack(string_to_hash("CHAR_FM_VEHICLE_1_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_VEHICLE_2_UNLCK"), -1);
	for (size_t i = 1; i <= 7; i++)
	{
		dStatPushBack(string_to_hash("CHAR_FM_CARMOD_" + std::to_string(i) + "_UNLCK"), -1);
	}
}

void gtav_cheats::unlock_medal()
{
	dStatPushBack(string_to_hash("AWD_100_KILLS_PISTOL"), 500);
	dStatPushBack(string_to_hash("AWD_100_KILLS_SNIPER"), 500);
	dStatPushBack(string_to_hash("AWD_50_KILLS_GRENADES"), 500);
	dStatPushBack(string_to_hash("AWD_100_KILLS_SHOTGUN"), 500);
	dStatPushBack(string_to_hash("AWD_100_KILLS_SMG"), 500);
	dStatPushBack(string_to_hash("AWD_50_KILLS_ROCKETLAUNCH"), 500);
	dStatPushBack(string_to_hash("AWD_25_KILLS_STICKYBOMBS"), 500);
	dStatPushBack(string_to_hash("AWD_20_KILLS_MELEE"), 500);
	dStatPushBack(string_to_hash("AWD_100_HEADSHOTS"), 500);
	dStatPushBack(string_to_hash("AWD_50_VEHICLES_BLOWNUP"), 500);
	dStatPushBack(string_to_hash("AWD_ENEMYDRIVEBYKILLS"), 500);
	dStatPushBack(string_to_hash("AWD_COPS_KILLED"), 500);
	dStatPushBack(string_to_hash("AWD_BUY_EVERY_GUN"), 1);
	dStatPushBack(string_to_hash("AWD_DRIVE_ALL_COP_CARS"), 1);
	dStatPushBack(string_to_hash("AWD_VEHICLE_JUMP_OVER_40M"), 50);
	dStatPushBack(string_to_hash("AWD_VEHICLE_JUMP0_OVER_40M"), 50);
	dStatPushBack(string_to_hash("AWD_VEHICLE_JUMP1_OVER_40M"), 50);
	dStatPushBack(string_to_hash("AWD_NO_ARMWRESTLING_WINS"), 50);
	dStatPushBack(string_to_hash("AWD_KILLS_MACHINEGUN"), 50);
	dStatPushBack(string_to_hash("AWD_ODD_JOBS"), 52);
	dStatPushBack(string_to_hash("AWD_PREPARATION"), 50);
	dStatPushBack(string_to_hash("AWD_ASLEEPONJOB"), 20);
	dStatPushBack(string_to_hash("AWD_DAICASHCRAB"), 100000);
	dStatPushBack(string_to_hash("AWD_BIGBRO"), 40);
	dStatPushBack(string_to_hash("AWD_SHARPSHOOTER"), 40);
	dStatPushBack(string_to_hash("AWD_RACECHAMP"), 40);
	dStatPushBack(string_to_hash("AWD_BATSWORD"), 1000000);
	dStatPushBack(string_to_hash("AWD_COINPURSE"), 950000);
	dStatPushBack(string_to_hash("AWD_ASTROCHIMP"), 3000000);
	dStatPushBack(string_to_hash("AWD_MASTERFUL"), 40000);
	dStatPushBack(string_to_hash("AWD_5STAR_WANTED_AVOIDANCE"), 50);
	dStatPushBack(string_to_hash("AWD_CAR_BOMBS_ENEMY_KILLS"), 50);
	dStatPushBack(string_to_hash("AWD_CARS_EXPORTED"), 50);
	dStatPushBack(string_to_hash("AWD_CONTROL_CROWDS"), 25);
	dStatPushBack(string_to_hash("AWD_DAILYOBJCOMPLETED"), 100);
	dStatPushBack(string_to_hash("AWD_DO_HEIST_AS_MEMBER"), 25);
	dStatPushBack(string_to_hash("AWD_DO_HEIST_AS_THE_LEADER"), 25);
	dStatPushBack(string_to_hash("AWD_DROPOFF_CAP_PACKAGES"), 100);
	dStatPushBack(string_to_hash("AWD_FINISH_HEIST_SETUP_JOB"), 50);
	dStatPushBack(string_to_hash("AWD_FINISH_HEISTS"), 50);
	dStatPushBack(string_to_hash("AWD_FM_DM_3KILLSAMEGUY"), 50);
	dStatPushBack(string_to_hash("AWD_FM_DM_KILLSTREAK"), 100);
	dStatPushBack(string_to_hash("AWD_FM_DM_STOLENKILL"), 50);
	dStatPushBack(string_to_hash("AWD_FM_DM_TOTALKILLS"), 500);
	dStatPushBack(string_to_hash("AWD_FM_DM_WINS"), 50);
	dStatPushBack(string_to_hash("AWD_FM_GOLF_HOLE_IN_1"), 300);
	dStatPushBack(string_to_hash("AWD_FM_GOLF_BIRDIES"), 25);
	dStatPushBack(string_to_hash("AWD_FM_GOLF_WON"), 25);
	dStatPushBack(string_to_hash("AWD_FM_GTA_RACES_WON"), 50);
	dStatPushBack(string_to_hash("AWD_FM_RACE_LAST_FIRST"), 25);
	dStatPushBack(string_to_hash("AWD_FM_RACES_FASTEST_LAP"), 50);
	dStatPushBack(string_to_hash("AWD_FM_SHOOTRANG_CT_WON"), 25);
	dStatPushBack(string_to_hash("AWD_FM_SHOOTRANG_RT_WON"), 25);
	dStatPushBack(string_to_hash("AWD_FM_SHOOTRANG_TG_WON"), 25);
	dStatPushBack(string_to_hash("AWD_FM_TDM_MVP"), 50);
	dStatPushBack(string_to_hash("AWD_FM_TDM_WINS"), 50);
	dStatPushBack(string_to_hash("AWD_FM_TENNIS_ACE"), 25);
	dStatPushBack(string_to_hash("AWD_FM_TENNIS_WON"), 25);
	dStatPushBack(string_to_hash("AWD_FMBASEJMP"), 25);
	dStatPushBack(string_to_hash("AWD_FMBBETWIN"), 50000);
	dStatPushBack(string_to_hash("AWD_FMCRATEDROPS"), 25);
	dStatPushBack(string_to_hash("AWD_FMDRIVEWITHOUTCRASH"), 30);
	dStatPushBack(string_to_hash("AWD_FMHORDWAVESSURVIVE"), 10);
	dStatPushBack(string_to_hash("AWD_FMKILLBOUNTY"), 25);
	dStatPushBack(string_to_hash("AWD_FMRALLYWONDRIVE"), 25);
	dStatPushBack(string_to_hash("AWD_FMRALLYWONNAV"), 25);
	dStatPushBack(string_to_hash("AWD_FMREVENGEKILLSDM"), 50);
	dStatPushBack(string_to_hash("AWD_FMSHOOTDOWNCOPHELI"), 25);
	dStatPushBack(string_to_hash("AWD_FMWINAIRRACE"), 25);
	dStatPushBack(string_to_hash("AWD_FMWINRACETOPOINTS"), 25);
	dStatPushBack(string_to_hash("AWD_FMWINSEARACE"), 25);
	dStatPushBack(string_to_hash("AWD_HOLD_UP_SHOPS"), 20);
	dStatPushBack(string_to_hash("AWD_KILL_CARRIER_CAPTURE"), 100);
	dStatPushBack(string_to_hash("AWD_KILL_PSYCHOPATHS"), 100);
	dStatPushBack(string_to_hash("AWD_KILL_TEAM_YOURSELF_LTS"), 25);
	dStatPushBack(string_to_hash("AWD_LAPDANCES"), 25);
	dStatPushBack(string_to_hash("AWD_LESTERDELIVERVEHICLES"), 25);
	dStatPushBack(string_to_hash("AWD_MENTALSTATE_TO_NORMAL"), 50);
	dStatPushBack(string_to_hash("AWD_NIGHTVISION_KILLS"), 100);
	dStatPushBack(string_to_hash("AWD_NO_HAIRCUTS"), 25);
	dStatPushBack(string_to_hash("AWD_ODISTRACTCOPSNOEATH"), 25);
	dStatPushBack(string_to_hash("AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
	dStatPushBack(string_to_hash("AWD_PARACHUTE_JUMPS_20M"), 50);
	dStatPushBack(string_to_hash("AWD_PARACHUTE_JUMPS_50M"), 50);
	dStatPushBack(string_to_hash("AWD_PASSENGERTIME"), 4);
	dStatPushBack(string_to_hash("AWD_PICKUP_CAP_PACKAGES"), 100);
	dStatPushBack(string_to_hash("AWD_RACES_WON"), 50);
	dStatPushBack(string_to_hash("AWD_SECURITY_CARS_ROBBED"), 25);
	dStatPushBack(string_to_hash("AWD_TAKEDOWNSMUGPLANE"), 50);
	dStatPushBack(string_to_hash("AWD_TIME_IN_HELICOPTER"), 4);
	dStatPushBack(string_to_hash("AWD_TRADE_IN_YOUR_PROPERTY"), 25);
	dStatPushBack(string_to_hash("AWD_VEHICLES_JACKEDR"), 500);
	dStatPushBack(string_to_hash("AWD_WIN_AT_DARTS"), 25);
	dStatPushBack(string_to_hash("AWD_WIN_CAPTURE_DONT_DYING"), 25);
	dStatPushBack(string_to_hash("AWD_WIN_CAPTURES"), 50);
	dStatPushBack(string_to_hash("AWD_WIN_GOLD_MEDAL_HEISTS"), 25);
	dStatPushBack(string_to_hash("AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	dStatPushBack(string_to_hash("AWD_DANCE_TO_SOLOMUN"), 100);
	dStatPushBack(string_to_hash("AWD_DANCE_TO_TALEOFUS"), 100);
	dStatPushBack(string_to_hash("AWD_DANCE_TO_DIXON"), 100);
	dStatPushBack(string_to_hash("AWD_DANCE_TO_BLKMAD"), 100);
	dStatPushBack(string_to_hash("AWD_CLUB_DRUNK"), 200);
	dStatPushBack(string_to_hash("AWD_WATCH_YOUR_STEP"), 50);
	dStatPushBack(string_to_hash("AWD_TOWER_OFFENSE"), 50);
	dStatPushBack(string_to_hash("AWD_READY_FOR_WAR"), 50);
	dStatPushBack(string_to_hash("AWD_THROUGH_A_LENS"), 50);
	dStatPushBack(string_to_hash("AWD_SPINNER"), 50);
	dStatPushBack(string_to_hash("AWD_YOUMEANBOOBYTRAPS"), 50);
	dStatPushBack(string_to_hash("AWD_MASTER_BANDITO"), 50);
	dStatPushBack(string_to_hash("AWD_SITTING_DUCK"), 50);
	dStatPushBack(string_to_hash("AWD_CROWDPARTICIPATION"), 50);
	dStatPushBack(string_to_hash("AWD_KILL_OR_BE_KILLED"), 50);
	dStatPushBack(string_to_hash("AWD_MASSIVE_SHUNT"), 25);
	dStatPushBack(string_to_hash("AWD_YOURE_OUTTA_HERE"), 200);
	dStatPushBack(string_to_hash("AWD_WEVE_GOT_ONE"), 50);
	dStatPushBack(string_to_hash("AWD_ARENA_WAGEWORKER"), 20000000);
	dStatPushBack(string_to_hash("AWD_TIME_SERVED"), 1000);
	dStatPushBack(string_to_hash("AWD_TOP_SCORE"), 500000);
	dStatPushBack(string_to_hash("AWD_CAREER_WINNER"), 1000);
}

void gtav_cheats::unlock_clothes()
{
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_1_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_2_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_3_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_4_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_5_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_6_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_7_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_8_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_9_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_10_UNLCK"), -1);
	dStatPushBack(string_to_hash("CHAR_FM_CLOTHES_11_UNLCK"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_OUTFIT"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_OUTFIT"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_HAIR_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_OUTFIT"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_OUTFIT"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_JBIB_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_JBIB_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_LEGS_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_LEGS_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_FEET_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_FEET_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_8"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_9"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_PROPS_10"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_TEETH"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_TEETH_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_TEETH_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_TEETH"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_TEETH_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_TEETH_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_BERD_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_BERD_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_TORSO"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_TORSO"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL2"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_SPECIAL2_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_3"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_4"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_5"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_6"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL_7"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL2"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_SPECIAL2_1"), -1);
	dStatPushBack(string_to_hash("CLTHS_AVAILABLE_DECL"), -1);
	dStatPushBack(string_to_hash("CLTHS_ACQUIRED_DECL"), -1);
	for (size_t i = 0; i <= 205; i++)
	{
		dStatPushBack(string_to_hash("DLC_APPAREL_ACQUIRED_" + std::to_string(i)), -1);
	}
	for (size_t i = 0; i <= 31; i++)
	{
		dStatPushBack(string_to_hash("ADMIN_CLOTHES_GV_BS_" + std::to_string(i)), -1);
	}
}

void gtav_cheats::casino_holocaust(int index)
{
	//清除等待时间
	dStatPushBack(string_to_hash("H3_COMPLETEDPOSIX"), -1);

	//解锁探查点
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), 0);
	dStatPushBack(string_to_hash("H3OPT_ACCESSPOINTS"), -1);
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), -1);

	//解锁兴趣点
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), 0);
	dStatPushBack(string_to_hash("H3OPT_POI"), -1);
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), -1);

	//抢劫方式
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), 0);
	switch (index)
	{
	case 0:
		dStatPushBack(string_to_hash("H3OPT_APPROACH"), 1);//潜行匿踪
		break;
	case 1:
		dStatPushBack(string_to_hash("H3OPT_APPROACH"), 2);//兵不厌诈
		break;
	default:
		dStatPushBack(string_to_hash("H3OPT_APPROACH"), 3);//气势汹汹
		break;
	}
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), -1);

	//抢劫钻石
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), 0);
	dStatPushBack(string_to_hash("H3OPT_TARGET"), 3);
	dStatPushBack(string_to_hash("H3OPT_BITSET1"), -1);

	//第二块任务板 - 全部最高等级
	dStatPushBack(string_to_hash("H3OPT_BITSET0"), 0);
	dStatPushBack(string_to_hash("H3OPT_DISRUPTSHIP"), 3);
	dStatPushBack(string_to_hash("H3OPT_KEYLEVELS"), 2);
	dStatPushBack(string_to_hash("H3OPT_CREWWEAP"), 5);
	dStatPushBack(string_to_hash("H3OPT_CREWDRIVER"), 5);
	dStatPushBack(string_to_hash("H3OPT_CREWHACKER"), 4);
	dStatPushBack(string_to_hash("H3OPT_VEHS"), 3);
	dStatPushBack(string_to_hash("H3OPT_WEAPS"), 0);
	dStatPushBack(string_to_hash("H3OPT_BITSET0"), -1);
}

gtav_cheats::gtav_cheats() {}

gtav_cheats::~gtav_cheats() { if (m_proc) CloseHandle(m_proc); }

void gtav_cheats::initialize_gtav()
{
	m_hwnd = FindWindowA(nullptr, "Grand Theft Auto V");
	error_handle(m_hwnd, "gtav窗口查找失败");

	GetWindowThreadProcessId(m_hwnd, &m_pid);
	error_handle(m_pid, "转化gtav进程id失败");

	m_proc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, 0, m_pid);
	error_handle(m_proc, "打开gtav进程句柄失败");

	if (get_mod_addr(L"steam_api64.dll"))//Steam
	{
		ADDRESS_WORLD = 0x24CD000;
		ADDRESS_BLIP = 0x1F524F0;
		ADDRESS_AMMO = 0x101BFBD;
		ADDRESS_MAGAZINE = 0x101BF78;
		ADDRESS_TUNABLE = 0x2D765E8;
		ADDRESS_WEAPON = 0x02810670;
		ADDRESS_GLOBAL = 0x2D765E0;
		ADDRESS_PLAYER_LIST = 0x1D98AE8;
		ADDRESS_REPLAY_INTERFACE = 0x1EC7E40;
	}
	else//Epic
	{
		ADDRESS_WORLD = 0x24C8858;
		ADDRESS_BLIP = 0x1F4F940;
		ADDRESS_AMMO = 0x101B6D9;
		ADDRESS_MAGAZINE = 0x101B694;
		ADDRESS_TUNABLE = 0x2D70DA8;
		ADDRESS_WEAPON = 0x0280E650;
		ADDRESS_GLOBAL = 0x2D70DA0;
		ADDRESS_PLAYER_LIST = 0x1D949A0;
		ADDRESS_REPLAY_INTERFACE = 0x1EC3828;
	}

	m_mod = get_mod_addr(L"GTA5.exe");
	error_handle(m_mod, "查找gtav主要模块失败");
}

void gtav_cheats::start_cheats()
{
	auto func = [&](bool state, bool& tip) -> void
	{
		if (state)
		{
			tip = !tip;
			m_show = true;
		}
	};

	while (true)
	{
		//更新地址
		update_addrs();

		//显示菜单
		show_menu();

		func(two_check(VK_MENU, VK_NUMPAD0), m_state_unlimited_endurance);
		func(two_check(VK_MENU, VK_NUMPAD1), m_state_npc_ignore_player);
		func(two_check(VK_MENU, VK_NUMPAD2), m_state_player_god_mode);
		func(two_check(VK_MENU, VK_NUMPAD3), m_state_never_fall);
		func(two_check(VK_MENU, VK_NUMPAD4), m_state_fake_dead_hide);
		func(two_check(VK_MENU, VK_NUMPAD5), m_state_vehicle_god_mode);
		func(two_check(VK_MENU, VK_NUMPAD6), m_state_infinite_jet);
		func(two_check(VK_MENU, VK_NUMPAD7), m_state_super_weapon_damage);
		func(two_check(VK_MENU, VK_NUMPAD8), m_state_unlimited_ammo);
		func(two_check(VK_MENU, VK_NUMPAD9), m_state_space_based_gun_without_cooling);
		func(two_check(VK_MENU, VK_ADD), m_state_unlock_bunker_research);
		func(two_check(VK_MENU, VK_SUBTRACT), m_state_anti_AFK_kick_out);
		func(two_check(VK_MENU, VK_DIVIDE), m_state_money_bag);
		func(two_check(VK_MENU, VK_MULTIPLY), m_state_no_reload);

		if (single_check(VK_F5)) move_to_target();
		if (single_check(VK_F6)) move_to_aim();
		if (single_check(VK_F7)) clear_wanted();
		if (single_check(VK_F8)) sit_in_personal_vehicle();

		if (two_check(VK_CONTROL, VK_NUMPAD0)) generate_vehicle(joaat("Oppressor2"));
		if (two_check(VK_CONTROL, VK_NUMPAD1)) generate_vehicle(joaat("kuruma2"));
		if (two_check(VK_CONTROL, VK_NUMPAD2)) generate_vehicle(joaat("deluxo"));
		if (two_check(VK_CONTROL, VK_NUMPAD3)) generate_vehicle(joaat("Vigilante"));
		if (two_check(VK_CONTROL, VK_NUMPAD4)) generate_vehicle(joaat("Lazer"));
		if (two_check(VK_CONTROL, VK_NUMPAD5)) generate_vehicle(joaat("Hydra"));
		if (two_check(VK_CONTROL, VK_NUMPAD6)) generate_vehicle(joaat("Buzzard"));
		if (two_check(VK_CONTROL, VK_NUMPAD7)) generate_vehicle(joaat("Dinghy4"));

		if (two_check(VK_TAB, VK_NUMPAD0)) full_character_attributes();
		if (two_check(VK_TAB, VK_NUMPAD1)) full_body_snacks();
		if (two_check(VK_TAB, VK_NUMPAD2)) unlock_car_accessories();
		if (two_check(VK_TAB, VK_NUMPAD3)) unlock_weapon_paint();
		if (two_check(VK_TAB, VK_NUMPAD4)) unlock_wholesale_price();
		if (two_check(VK_TAB, VK_NUMPAD5)) unlock_medal();
		if (two_check(VK_TAB, VK_NUMPAD6)) unlock_clothes();

		if (two_check(VK_CAPITAL, VK_NUMPAD0)) casino_holocaust(0);
		if (two_check(VK_CAPITAL, VK_NUMPAD1)) casino_holocaust(1);
		if (two_check(VK_CAPITAL, VK_NUMPAD2)) casino_holocaust(2);
		if (two_check(VK_CAPITAL, VK_NUMPAD3)) battle_handle(-1);
		if (two_check(VK_CAPITAL, VK_NUMPAD4)) battle_handle(0);
		if (two_check(VK_CAPITAL, VK_NUMPAD5)) kill_self();

		unlimited_endurance(m_state_unlimited_endurance);
		npc_ignore_player(m_state_npc_ignore_player);
		player_god_mode(m_state_player_god_mode);
		never_fall(m_state_never_fall);
		fake_dead_hide(m_state_fake_dead_hide);
		vehicle_god_mode(m_state_vehicle_god_mode);
		infinite_jet(m_state_infinite_jet);
		super_weapon_damage(m_state_super_weapon_damage);
		unlimited_ammo(m_state_unlimited_ammo);
		space_based_gun_without_cooling(m_state_space_based_gun_without_cooling);
		unlock_bunker_research(m_state_unlock_bunker_research);
		anti_AFK_kick_out(m_state_anti_AFK_kick_out);
		money_bag(m_state_money_bag);
		no_reload(m_state_no_reload);

		handle_queue();

		Sleep(100);
	}
}