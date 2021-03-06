﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	/// <summary>
	/// オブジェクトの親子関係の同期方法を表す列挙体。
	/// </summary>
	public enum ChildMode
	{
		/// <summary>
		/// 位置のみを同期する。
		/// </summary>
		Position = swig.eChildMode.CHILD_MODE_POSITION,
		/// <summary>
		/// 位置・角度・拡大率を同期する。
		/// </summary>
		All = swig.eChildMode.CHILD_MODE_ALL,
		/// <summary>
		/// 同期を行わない。
		/// </summary>
		Nothing = swig.eChildMode.CHILD_MODE_NOTHING
	}
}
