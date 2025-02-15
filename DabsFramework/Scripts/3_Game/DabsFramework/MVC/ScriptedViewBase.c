#define DABSFRAMEWORK_1_51

// Base type for all primary view Types (ScriptView, Controller, ViewBinding)
class ScriptedViewBase: Managed
{
	// Enable verbose logging
	[NonSerialized()]
	reference bool Debug_Logging;

	// Source Widget
	[NonSerialized()]
	protected Widget m_LayoutRoot;

	// Source Widget Controller
	[NonSerialized()]
	protected ref WidgetController m_WidgetController;

	// ScriptedViewBase Type Converter
	[NonSerialized()]
	protected ref TypeConverter m_TypeConverter;

	// ScriptedViewBase parent
	[NonSerialized()]
	protected ScriptedViewBase m_ParentScriptedViewBase;

	void ScriptedViewBase()
	{
		if (Debug_Logging) {
			PrintFormat("[Log] %1", this);
		}

#ifdef WORKBENCH
		if (!GetDayZGame()) {
			return;
		}
#endif
		
		m_TypeConverter = GetDayZGame().GetTypeConversion(Type());
		if (!m_TypeConverter) {
			Error("Could not generate TypeConverter on %1", Type().ToString());
			return;
		}
		
		m_TypeConverter.Set(this);
	}

	void ~ScriptedViewBase()
	{
		if (Debug_Logging) {
			PrintFormat("[Log] ~%1", this);
		}
	}
	
	void Show(bool show)
	{
		if (m_LayoutRoot) {
			m_LayoutRoot.Show(show);
		}
	}
	
	bool IsVisible()
	{
		return m_LayoutRoot && m_LayoutRoot.IsVisible();
	}
	
	void SetParent(ScriptedViewBase parent)
	{
		m_ParentScriptedViewBase = parent;

		// Propagates debug logging even if disabled locally
		Debug_Logging = Debug_Logging || m_ParentScriptedViewBase.Debug_Logging;
	}

	void OnWidgetScriptInit(Widget w)
	{
		Trace("OnWidgetScriptInit %1", w.ToString());
		m_LayoutRoot = w;
		
#ifdef WORKBENCH
		if (!GetDayZGame()) {
			return;
		}
#endif
		
		m_WidgetController = GetDayZGame().GetWidgetController(m_LayoutRoot);
		
		if (!m_WidgetController) {
			Error("Could not find WidgetController for type %1\n\nOverride GetDayZGame().RegisterWidgetControllers to register custom WidgetControllers", m_LayoutRoot.GetTypeName());
			return;
		}
	}

	ScriptedViewBase GetScriptedRoot()
	{
		ScriptedViewBase view_base = this;
		FindScriptedRoot(view_base);
		return view_base;
	}

	static void FindScriptedRoot(out ScriptedViewBase view_base)
	{
		if (view_base && view_base.GetParent()) {
			view_base = view_base.GetParent();
			FindScriptedRoot(view_base);
		}
	}
	
	// recursive function searches up the tree for the first available script view
	static ScriptedViewBase GetParentScriptView(Widget widget)
	{		
		if (!widget) {
			return null;
		}
		
		ScriptedViewBase scripted_view;
		widget.GetScript(scripted_view);
		
		if (scripted_view)  {
			return scripted_view;
		}
		
		widget = widget.GetParent();
		return GetParentScriptView(widget);
	}

	void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging)
			PrintFormat("[Trace] %1 - %2 ", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
		//#endif
	}

	void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging)
			PrintFormat("[Log] %1 - %2", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
		//#endif
	}

	void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		string header = string.Format("[Error] %1", Type());
		Error2(header, msg);
	}

	// ### Events are invoked up heirarchy, starting at ViewController, and up to ScriptView
	bool OnClick(Widget w, int x, int y, int button)
	{
		Trace("OnClick: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnClick(w, x, y, button));
	}

	bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		Trace("OnModalResult: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnModalResult(w, x, y, code, result));
	}

	bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		Trace("OnDoubleClick: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDoubleClick(w, x, y, button));
	}

	bool OnSelect(Widget w, int x, int y)
	{
		Trace("OnSelect: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnSelect(w, x, y));
	}

	bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		Trace("OnItemSelected: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnItemSelected(w, x, y, row, column, oldRow, oldColumn));
	}

	bool OnFocus(Widget w, int x, int y)
	{
		Trace("OnFocus: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnFocus(w, x, y));
	}

	bool OnFocusLost(Widget w, int x, int y)
	{
		Trace("OnFocusLost: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnFocusLost(w, x, y));
	}

	bool OnMouseEnter(Widget w, int x, int y)
	{
		Trace("OnMouseEnter: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnMouseEnter(w, x, y));
	}

	bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		Trace("OnMouseLeave: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnMouseLeave(w, enterW, x, y));
	}

	bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		Trace("OnMouseWheel: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnMouseWheel(w, x, y, wheel));
	}

	bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonDown: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnMouseButtonDown(w, x, y, button));
	}

	bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonUp: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnMouseButtonUp(w, x, y, button));
	}

	bool OnController(Widget w, int control, int value)
	{
		Trace("OnController: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnController(w, control, value));
	}

	bool OnKeyDown(Widget w, int x, int y, int key)
	{
		Trace("OnKeyDown: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnKeyDown(w, x, y, key));
	}

	bool OnKeyUp(Widget w, int x, int y, int key)
	{
		Trace("OnKeyUp: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnKeyUp(w, x, y, key));
	}

	bool OnKeyPress(Widget w, int x, int y, int key)
	{
		Trace("OnKeyPress: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnKeyPress(w, x, y, key));
	}

	bool OnChange(Widget w, int x, int y, bool finished)
	{
		Trace("OnChange: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnChange(w, x, y, finished));
	}

	bool OnDrag(Widget w, int x, int y)
	{
		Trace("OnDrag: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDrag(w, x, y));
	}

	bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDragging: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDragging(w, x, y, reciever));
	}

	bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDraggingOver: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDraggingOver(w, x, y, reciever));
	}

	bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDrop: %1 - Reciever: %2", w.GetName(), reciever.ToString());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDrop(w, x, y, reciever));
	}

	bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDropReceived: %1 - Reciever: %2", w.GetName(), reciever.ToString());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnDropReceived(w, x, y, reciever));
	}

	bool OnResize(Widget w, int x, int y)
	{
		Trace("OnResize: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnResize(w, x, y));
	}

	bool OnChildAdd(Widget w, Widget child)
	{
		Trace("OnChildAdd: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnChildAdd(w, child));
	}

	bool OnChildRemove(Widget w, Widget child)
	{
		Trace("OnChildRemove: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnChildRemove(w, child));
	}

	bool OnUpdate(Widget w)
	{
		Trace("OnUpdate: %1", w.GetName());
		return (m_ParentScriptedViewBase && m_ParentScriptedViewBase.OnUpdate(w));
	}
		
	ScriptedViewBase GetParent()
	{		
		return m_ParentScriptedViewBase;
	}
	
	Widget GetLayoutRoot()
	{
		return m_LayoutRoot;
	}
	
	WidgetController GetWidgetController()
	{
		return m_WidgetController;
	}
	
	TypeConverter GetTypeConversion()
	{
		return m_TypeConverter;
	}
}