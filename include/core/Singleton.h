/*
 * Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Abstract: 
 */


#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "Uncopyable.h"


/**
 * Any class that inherits from Singleton become itself a singleton.
 *
 * \remark
 * Singleton can't be copied and can't be instanciated (new).
 *
 * \author  Constantin Masson
 */
template<class T> class Singleton : virtual private Uncopyable<Singleton<T>>
{
private:
	friend T;

private:
	// Can't be instanciated
	Singleton() = default;

	virtual ~Singleton() = default;

public:
        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static T& getInstance()
	{
		static T m;

		return m;
        }

        /**
         * Returns the pointer to the singleton instance.
         *
         * \return Pointer to the singleton instance.
         */
        static T* getInstancePtr()
	{
		return &Singleton<T>::getSingleton();
        }
};

#endif // #ifndef _SINGLETON_H_
