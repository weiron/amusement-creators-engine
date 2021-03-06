﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
    public class JoystickContainer
    {
        private ace.swig.JoystickContainer joystickContainer;
        private const int MAX_JOYSTICK_NUM=16;
        private Joystick[] joysticks;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="jc">ネイティブインタフェース</param>
        internal JoystickContainer(ace.swig.JoystickContainer jc)
        {
            joystickContainer = jc;
            joysticks = new Joystick[MAX_JOYSTICK_NUM];
            for(int i=0;i<MAX_JOYSTICK_NUM;++i)
            {
                joysticks[i] = new Joystick(joystickContainer.GetJoystickAt(i));
            }
        }

        /// <summary>
        /// 引数に指定した番目のジョイスティックが接続されているかを返す
        /// </summary>
        /// <param name="at">何番目のジョイスティックの接続を確認するか</param>
        /// <returns>接続されているか否か</returns>
        public bool IsPresentAt(int at)
        {
            return joystickContainer.IsPresentAt(at);
        }

        /// <summary>
        /// 引数に指定した番目のジョイスティッククラスを返す
        /// </summary>
        /// <param name="at">何番目のジョイスティッククラスをとるか</param>
        /// <returns>ジョイスティッククラス</returns>
        public ace.Joystick GetJoystickAt(int at)
        {
            return joysticks[at];
        }
    }
}
