package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import de.ajaxgui.ext.JsGenerator;

public class CheckBox extends AbstractButton {
	private ArrayList<Object> checkedChangedObject = new ArrayList<Object>();

	private ArrayList<String> checkedChangedFunc = new ArrayList<String>();

	public boolean checked = false;

	private String text = "";

	public CheckBox(String text) {
		super(text);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxCheckBox(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName()
				+ ".addEventListener(\"changeChecked\", checkedChangedEvent);");
	}

	public boolean isChecked() {
		return checked;
	}

	public void setChecked(boolean checked) {
		this.checked = checked;
		if (checked)
			JsGenerator.get().addLine(getVarName() + ".setChecked(true);");
		else
			JsGenerator.get().addLine(getVarName() + ".setChecked(false);");
	}

	public void addCheckedChanged(Object o, String func) {
		checkedChangedObject.add(o);
		checkedChangedFunc.add(func);
	}

	public void doCheckedChanged() {
		for (int i = 0; i < checkedChangedObject.size(); i++) {
			Object obj = checkedChangedObject.get(i);
			String func = checkedChangedFunc.get(i);
			Class cl = obj.getClass();
			Method m;
			try {
				m = cl.getMethod(func, new Class[] {});
				try {
					m.invoke(obj);
				} catch (IllegalArgumentException e) {
					e.printStackTrace();
				} catch (InvocationTargetException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			}
		}
	}
}
