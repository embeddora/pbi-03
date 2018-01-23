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

#ifndef _UNCOPYABLE_H_
#define _UNCOPYABLE_H_


/**
 * Any class that inherits from Uncopyable cannot be copied anymore.
 *
 * \remark
 * In order to disable totally object copy,
 * Copy constructor and copy operator are disabled.
 *
 * \author  Constantin Masson
 */

template<class T> class Uncopyable
{
public:
	Uncopyable() = default;

	virtual ~Uncopyable() = default;

private:
	Uncopyable(Uncopyable<T> const& other) = delete;

	Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};

#endif // #ifndef _UNCOPYABLE_H_
