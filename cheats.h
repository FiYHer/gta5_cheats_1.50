#pragma once
#include "util.h"

class gtav_cheats
{
private:
	r_hwnd m_hwnd;			//gtav窗口句柄
	r_dword m_pid;			//gtav进程ID
	r_handle m_proc;			//gtav进程句柄
	r_hmodue m_mod;		//gtav主要模块

private:
	long		ADDRESS_WORLD = 0;
	long		ADDRESS_BLIP = 0;
	long		ADDRESS_AMMO = 0;
	long		ADDRESS_MAGAZINE = 0;
	long		ADDRESS_TUNABLE = 0;
	long		ADDRESS_WEAPON = 0;
	long		ADDRESS_GLOBAL = 0;
	long		ADDRESS_PLAYER_LIST = 0;
	long		ADDRESS_REPLAY_INTERFACE = 0;

private:
	r_dword_ptr m_dwpWorldBase = 0;
	r_dword_ptr m_dwpTunableBase = 0;
	r_dword_ptr m_dwpGlobalBase = 0;

	r_dword_ptr m_dwpReplayInterfaceBase = 0;
	r_dword_ptr m_Replay_dwpPedInterface = 0;
	r_dword_ptr m_Replay_dwpPedList = 0;

	r_dword_ptr m_dwpPlayerBase = 0;
	r_dword_ptr m_Player_dwpPosBase = 0;
	r_dword_ptr m_Player_dwpPlayerInfo = 0;
	r_dword_ptr m_Player_dwpAttackerBase = 0;

	r_dword_ptr m_dwpVehicleBase = 0;
	r_dword_ptr m_Vehicle_dwpPosBase = 0;
	r_dword_ptr m_Vehicle_dwpHandling = 0;

	r_dword_ptr m_dwpWeaponBase = 0;
	r_dword_ptr m_dwpWeaponManager = 0;
	r_dword_ptr m_dwpWeaponCur = 0;
	r_dword_ptr m_dwpAmmoInfo = 0;

private:
	std::vector<hash_table> m_queue;
	inline void dStatPushBack(unsigned int _hash, int _value) { m_queue.push_back({ _hash,_value }); }

private:
	bool m_show = true;

	bool m_state_unlimited_endurance = true;
	bool m_state_npc_ignore_player = true;
	bool m_state_player_god_mode = true;
	bool m_state_never_fall = true;
	bool m_state_fake_dead_hide = false;
	bool m_state_vehicle_god_mode = true;
	bool m_state_infinite_jet = false;
	bool m_state_super_weapon_damage = true;
	bool m_state_unlimited_ammo = true;
	bool m_state_space_based_gun_without_cooling = true;
	bool m_state_unlock_bunker_research = false;
	bool m_state_anti_AFK_kick_out = true;
	bool m_state_money_bag = false;
	bool m_state_no_reload = false;

private:
	//查找指定名称的mod
	r_hmodue get_mod_addr(const r_wchar* str);

	//更新地址列表
	void update_addrs();

	//显示菜单
	void show_menu();

	//获取标记点
	vector_2 get_target_point();

	//获取任务点
	vector_3 get_aim_point();

	//开始传送
	void start_move(vector_3 dest);

private:
	//读取内存
	template<class T>
	T read(r_dword_ptr addr)
	{
		T result;
		r_size_t size = sizeof(T);
		r_size_t finish = 0;
		r_dword old_protect = 0;

		VirtualProtectEx(m_proc, (LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &old_protect);
		ReadProcessMemory(m_proc, (LPCVOID)addr, &result, size, &finish);
		VirtualProtectEx(m_proc, (LPVOID)addr, size, old_protect, &old_protect);

		return result;
	}

	//写入内存
	template<class T>
	void write(r_dword_ptr addr, T buffer)
	{
		r_size_t size = sizeof(T);
		r_size_t finish = 0;
		r_dword old_protect = 0;

		VirtualProtectEx(m_proc, (LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &old_protect);
		WriteProcessMemory(m_proc, (LPVOID)addr, &buffer, size, &finish);
		VirtualProtectEx(m_proc, (LPVOID)addr, size, old_protect, &old_protect);
	}

private:
	//传送到目标点
	void move_to_target();

	//传送到任务点
	void move_to_aim();

	//取消通缉等级
	void clear_wanted();

	//自杀
	void kill_self();

	//坐进个人载具
	void sit_in_personal_vehicle();

	//无限耐力
	void unlimited_endurance(bool state);

	//npc忽略玩家
	void npc_ignore_player(bool state);

	//玩家上帝模式
	void player_god_mode(bool state);

	//永不摔倒
	void never_fall(bool state);

	//假死雷达隐藏
	void fake_dead_hide(bool state);

	//车辆上帝模式
	void vehicle_god_mode(bool state);

	//无限喷射
	void infinite_jet(bool state);

	//无敌超级伤害
	void super_weapon_damage(bool state);

	//无需换弹
	void no_reload(bool state);

	//无限弹药
	void unlimited_ammo(bool state);

	//天基炮无冷却
	void space_based_gun_without_cooling(bool state);

	//临时解锁地堡研究
	void unlock_bunker_research(bool state);

	//反AFK踢出
	void anti_AFK_kick_out(bool state);

	//钱袋刷钱
	void money_bag(bool state);

	//列表信息处理
	void handle_queue();

	//加入战局处理
	void battle_handle(int tip);

	//生成载具
	void generate_vehicle(unsigned int val, float pos = 6.0f);

	//角色属性全满
	void full_character_attributes();

	//零食防弹衣全满
	void full_body_snacks();

	//解锁改车配件
	void unlock_car_accessories();

	//解锁武器涂装
	void unlock_weapon_paint();

	//解锁批发价
	void unlock_wholesale_price();

	//解锁奖章
	void unlock_medal();

	//解锁衣服
	void unlock_clothes();

	//赌场豪劫
	void casino_holocaust(int index);

public:
	gtav_cheats();
	~gtav_cheats();

	//初始化gtav
	void initialize_gtav();

	//开始grav作弊
	void start_cheats();
};
