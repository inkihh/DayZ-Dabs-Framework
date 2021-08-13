class NetworkLightBase: Building
{
	protected ScriptedLightBase m_Light;
	
	// All of these are assigned to the default light parameters
	bool CastShadow = true;
	bool EnableSpecular = true;
	bool EnableLinear = true;
	float PulseCoef = 0.0;
	bool VisibleDuringDay = false;
	float Radius = 50;
	
	// Heat Haze
	bool HeatHaze = false;
	float HeatHazeRadius = 0;
	float HeatHazePower = 0;
	
	// Colors and brightness
	int DiffuseColor = ARGB(255, 255, 255, 255);
	int AmbientColor = ARGB(255, 255, 255, 255);
	float Brightness = 1.0;
	
	// Flare
	bool FlareVisible = true;
	vector FlareRelativePosition;// = GetFlareRelPosition();
	
	// Spotlight
	float SpotLightAngle = 90;
	
	void NetworkLightBase()
	{
		if (GetGame().IsMultiplayer()) {
			// Booleans
			RegisterNetSyncVariableBool("CastShadow");
			RegisterNetSyncVariableBool("EnableSpecular");
			RegisterNetSyncVariableBool("EnableLinear");
			RegisterNetSyncVariableBool("VisibleDuringDay");
			RegisterNetSyncVariableBool("HeatHaze");
			RegisterNetSyncVariableBool("FlareVisible");
			
			// Ints
			RegisterNetSyncVariableInt("DiffuseColor");
			RegisterNetSyncVariableInt("AmbientColor");
			
			// Floats
			RegisterNetSyncVariableFloat("PulseCoef");
			RegisterNetSyncVariableFloat("Radius");
			RegisterNetSyncVariableFloat("HeatHazeRadius");
			RegisterNetSyncVariableFloat("HeatHazePower");
			RegisterNetSyncVariableFloat("Brightness");
			RegisterNetSyncVariableFloat("SpotLightAngle");
		}
		
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			m_Light = CreateLight();
			m_Light.AttachOnObject(this);
		}
	}
	
	void ~NetworkLightBase()
	{
		if (m_Light) {
			m_Light.Destroy();
		}
	}
	
	ScriptedLightBase CreateLight(vector global_pos = "0 0 0", float fade_in_time_in_s = 0)
	{
		return ScriptedLightBase.CreateLight(ScriptedLightBase, global_pos, fade_in_time_in_s);
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (!GetGame().IsMultiplayer() || !m_Light) {
			return;
		}
		
		float a, r, g, b;

		m_Light.SetCastShadow(CastShadow);
		m_Light.EnableSpecular(EnableSpecular);
		m_Light.EnableLinear(EnableLinear);
		m_Light.SetPulseCoef(PulseCoef);
		m_Light.SetVisibleDuringDaylight(VisibleDuringDay);	
		m_Light.SetRadiusTo(Radius);
		m_Light.EnableHeatHaze(HeatHaze);
		m_Light.SetHeatHazeRadius(HeatHazeRadius);
		m_Light.SetHeatHazePower(HeatHazePower);

		InverseARGBF(DiffuseColor, a, r, g, b);
		m_Light.SetDiffuseColor(r, g, b);
		m_Light.SetDiffuseAlpha(a);

		InverseARGBF(AmbientColor, a, r, g, b);
		m_Light.SetAmbientColor(r, g, b);
		m_Light.SetAmbientAlpha(a);
		m_Light.SetBrightnessTo(Brightness);
		m_Light.SetFlareVisible(FlareVisible);
		m_Light.SetFlareRelPosition(FlareRelativePosition);
		m_Light.SetSpotLightAngle(SpotLightAngle);
	}
	
	void PropertyChanged(string property_name)
	{
		float a, r, g, b;
		switch (property_name) {
			case "CastShadow": {
				m_Light.SetCastShadow(CastShadow);
				break;
			}
			
			case "EnableSpecular": {
				m_Light.EnableSpecular(EnableSpecular);
				break;
			}
			
			case "EnableLinear": {
				m_Light.EnableLinear(EnableLinear);
				break;
			}
			
			case "PulseCoef": {
				m_Light.SetPulseCoef(PulseCoef);
				break;
			}
			
			case "VisibleDuringDay": {
				m_Light.SetVisibleDuringDaylight(VisibleDuringDay);
				break;
			}
			
			case "Radius": {
				m_Light.SetRadiusTo(Radius);
				break;
			}
			
			case "HeatHaze": {
				m_Light.EnableHeatHaze(HeatHaze);
				break;
			}
			
			case "HeatHazeRadius": {
				m_Light.SetHeatHazeRadius(HeatHazeRadius);
				break;
			}
			
			case "HeatHazePower": {
				m_Light.SetHeatHazePower(HeatHazePower);
				break;
			}
			
			case "DiffuseColor": {
				InverseARGBF(DiffuseColor, a, r, g, b);
				m_Light.SetDiffuseColor(r, g, b);
				m_Light.SetDiffuseAlpha(a);
				break;
			}			
			
			case "AmbientColor": {
				InverseARGBF(AmbientColor, a, r, g, b);
				m_Light.SetAmbientColor(r, g, b);
				m_Light.SetAmbientAlpha(a);
				break;
			}
			
			case "Brightness": {
				m_Light.SetBrightnessTo(Brightness);
				break;
			}
			
			case "FlareVisible": {
				m_Light.SetFlareVisible(FlareVisible);
				break;
			}
			
			case "FlareRelativePosition": {
				m_Light.SetFlareRelPosition(FlareRelativePosition);
				break;
			}
			
			case "SpotLightAngle": {
				m_Light.SetSpotLightAngle(SpotLightAngle);
				break;
			}
		}
	}
}