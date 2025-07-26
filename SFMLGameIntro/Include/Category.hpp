#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
    enum Type
    {
		None				= 0,
		SceneAirLayer		= 1 << 0, // 1
		PlayerAircraft		= 1 << 1, // 2
		AlliedAircraft		= 1 << 2, // 4
		EnemyAircraft		= 1 << 3, // 8
		Pickup				= 1 << 4, // 16
		AlliedProjectile	= 1 << 5, // 32
		EnemyProjectile		= 1 << 6, // 64

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft, // 14
		Projectile = AlliedProjectile | EnemyProjectile, // 96
    };
};

#endif // CATEGORY_H