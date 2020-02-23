// Copyright (C) 2011, 2012 Zeno Gantner
// Copyright (C) 2010 Steffen Rendle, Zeno Gantner
//
// This file is part of MyMediaLite.
//
// MyMediaLite is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MyMediaLite is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with MyMediaLite.  If not, see <http://www.gnu.org/licenses/>.
using System;
using System.Collections.Generic;
using MyMediaLite.DataType;

namespace MyMediaLite.Correlation
{
	/// <summary>Class for storing cosine similarities</summary>
	/// <remarks>
	/// http://en.wikipedia.org/wiki/Cosine_similarity
	/// </remarks>
	public sealed class BinaryCosine : BinaryDataSymmetricCorrelationMatrix
	{
		/// <summary>Creates an object of type Cosine</summary>
		/// <param name="num_entities">the number of entities</param>
		public BinaryCosine(int num_entities) : base(num_entities) { }

		///
		protected override float ComputeCorrelationFromOverlap(float overlap, float count_x, float count_y)
		{
            /// Weighted�� false�� ���
            /// 1. overlap : overlap[x,y]�� user(or item) x �� user(or item) y�� �������� ���� items(users) ��
            /// 2. count_x(or y) : user(or item) x(or y)�� ���� items(users) ��
            /// -> ��, �� users�� �������� ���� items�� ���� ���� ����ġ�� Ŀ��

            /// Weighted�� true�� ���
            /// 1. overlap : overlap[x,y]�� user(or item) x �� user(or item) y�� �������� ���� items(users)�� ����ġ�� ������ ��
            /// 2. count_x(or y) : user(or item) x(or y)�� ���� items(users)�� ����ġ ��
            /// -> ��, �� users�� �������� ���� items�� ���� ���� ����ġ�� Ŀ������, �ش� items�� ��� users���� �򰡵� �󵵰� ���� ���� ����ġ�� ������.
			double size_product = count_x * count_y;
			if (size_product > 0.0)
				return (float) (overlap / Math.Sqrt(size_product));
			else
				return 0.0f;
		}
	}
}