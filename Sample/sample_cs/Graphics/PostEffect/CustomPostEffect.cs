﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ace;

namespace test_cs.Graphics.PostEffect
{
	class CustomPostEffect : ISample
	{

		static string shader2d_dx_ps = @"

Texture2D		g_texture		: register( t0 );
SamplerState	g_sampler		: register( s0 );

float3			g_values		: register( c0 );

float4 main( const PS_Input Input ) : SV_Target
{
	float4 outputedColor = g_texture.Sample(g_sampler, Input.UV);
	if(outputedColor.a == 0.0f) discard;

	float2 localPos = float2( (Input.Pos.x + 1.0) / 2.0 * g_values.x, (Input.Pos.y + 1.0) / 2.0 * g_values.y );
	float2 centerPos = float2( g_values.x / 2.0, g_values.y / 2.0 );

	if( (localPos.x - centerPos.x) * (localPos.x - centerPos.x) + (localPos.y - centerPos.y) * (localPos.y - centerPos.y) < g_values.z * g_values.z )
	{
		outputedColor.r = 1.0 - outputedColor.r;
		outputedColor.g = 1.0 - outputedColor.g;
		outputedColor.b = 1.0 - outputedColor.b;
	}

	return outputedColor;
}


";

		static string shader2d_gl_ps = @"

uniform sampler2D	g_texture;

uniform vec3		g_values;

void main()
{
	vec4 outputedColor = texture2D(g_texture, inUV.xy);

	vec2 localPos = vec2( (inPos.x + 1.0) / 2.0 * g_values.x, (inPos.y + 1.0) / 2.0 * g_values.y );
	vec2 centerPos = vec2( g_values.x / 2.0, g_values.y / 2.0 );

	if( (localPos.x - centerPos.x) * (localPos.x - centerPos.x) + (localPos.y - centerPos.y) * (localPos.y - centerPos.y) < g_values.z * g_values.z )
	{
		outputedColor.r = 1.0 - outputedColor.r;
		outputedColor.g = 1.0 - outputedColor.g;
		outputedColor.b = 1.0 - outputedColor.b;
	}

	gl_FragColor = outputedColor; 
}

";

		class PostEffect : ace.PostEffect
		{

			Shader2D m_shader;
			Material2D m_material2d;

			public PostEffect(ace.Graphics g)
			{
				List<ace.ShaderVariableProperty> props = new List<ShaderVariableProperty>();
				var prop_tex = new ace.ShaderVariableProperty();
				prop_tex.Name = "g_texture";
				prop_tex.Offset = 0;
				prop_tex.Type = ace.ShaderVariableType.Texture2D;
				props.Add(prop_tex);

				var prop_v = new ace.ShaderVariableProperty();
				prop_v.Name = "g_values";
				prop_v.Offset = 0;
				prop_v.Type = ace.ShaderVariableType.Vector3DF;
				props.Add(prop_v);
				
				if (g.GraphicsType == GraphicsType.DirectX11)
				{
					m_shader = g.CreateShader2D(
						shader2d_dx_ps,
						props.ToArray()
						);
				}
				else if (g.GraphicsType == GraphicsType.OpenGL)
				{
					m_shader = g.CreateShader2D(
						shader2d_gl_ps,
						props.ToArray()
						);
				}
				else
				{
					throw new Exception();
				}

				m_material2d = g.CreateMaterial2D(m_shader);
			}

			public override void OnDraw(ace.RenderTexture2D dst, ace.RenderTexture2D src)
			{
				m_material2d.SetTexture2D("g_texture", src);
				m_material2d.SetVector3DF("g_values", new Vector3DF(640,480,200));

				DrawOnTexture2DWithMaterial(dst, m_material2d);
			}
		}

		public void Run()
		{
			Engine.Initialize("CustomPostEffect", 640, 480, new EngineOption());

			var scene = new Scene();
			var layer = new Layer2D();
			var obj = new TextureObject2D()
			{
				Texture = Engine.Graphics.CreateTexture2D("Data/Texture/Sample1.png"),
			};

			layer.AddObject(obj);
			layer.AddPostEffect(new PostEffect(Engine.Graphics));
			scene.AddLayer(layer);
			Engine.ChangeScene(scene);

			while (Engine.DoEvents())
			{
				Engine.Update();
			}

			Engine.Terminate();
		}

	}
}
