﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
    /// <summary>
    /// マウスの左右ボタンの状態を扱うクラス
    /// </summary>
    public class SideButton:IMouseButtonState
    {
        /// <summary>
        /// 押下状態を保持する変数
        /// </summary>
        private MouseButtonState mouseButtonState;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        internal SideButton() { }

        /// <summary>
        /// 押下状態をセットする関数
        /// </summary>
        /// <param name="mButtonState">押下状態</param>
        internal void SetState(MouseButtonState mButtonState)
        {
            mouseButtonState=mButtonState;
        }

        /// <summary>
        /// 押下状態を返すプロパティ
        /// </summary>
        public MouseButtonState ButtonState
        {
            get { return mouseButtonState; }
        }
    }
}
