//
//  Created by huanghaifeng on 15-11-24.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef SPINLOCK_HEADER
#define SPINLOCK_HEADER

// int lock;
#define SPINLOCK_INIT(lock) lock=0
#define SPINLOCK_LOCK(lock) while(__sync_lock_test_and_set(&lock,1)){}
#define SPINLOCK_TRYLOCK(lock) (__sync_lock_test_and_set(&lock,1) == 0)
#define SPINLOCK_UNLOCK(lock) __sync_lock_release(&lock)

#endif

