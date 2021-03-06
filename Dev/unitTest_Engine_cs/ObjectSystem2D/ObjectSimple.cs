﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ace;

namespace unitTest_Engine_cs.ObjectSystem2D
{
	class ObjectSimple : EngineTest
	{
		public ObjectSimple()
			: base( 60 )
		{
		}

		protected override void OnStart()
		{
			var scene = new Scene();
			var layer = new Layer2D();
			obj = new TextureObject2D()
			{
				Texture = Engine.Graphics.CreateTexture2D( "Data/Texture/Cloud1.png" ),
				Position = new Vector2DF( 320, 240 ),
				Angle = 5,
				CenterPosition = new Vector2DF( 128, 128 ),
			};

			layer.AddObject( obj );
			scene.AddLayer( layer );
			Engine.ChangeScene( scene );
		}

		protected override void OnUpdating()
		{
			obj.Scale += new Vector2DF( 0.0008f, 0.0008f );
		}

		private TextureObject2D obj;
	}
}
