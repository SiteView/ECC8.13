package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import de.ajaxgui.ext.JsGenerator;

public class TextField extends Control {

	public String text = "";

	private ArrayList<String> textChangedFunc = new ArrayList<String>();

	private ArrayList<Object> textChangedObject = new ArrayList<Object>();

	public TextField() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTextField();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName()
				+ ".addEventListener(\"changeValue\", textChangedEvent);");
	}

	public void addTextChanged(Object o, String func) {
		textChangedObject.add(o);
		textChangedFunc.add(func);
	}

	public void doTextChanged() {
		for (int i = 0; i < textChangedObject.size(); i++) {
			Object obj = textChangedObject.get(i);
			String func = textChangedFunc.get(i);
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

	public String getText() {
		return text;
	}

	public void setReadOnly(boolean bool) {
		if (bool)
			JsGenerator.get().addLine(getVarName() + ".setReadOnly(true);");
		else
			JsGenerator.get().addLine(getVarName() + ".setReadOnly(false);");
	}

	public void setText(String text) {
		this.text = text;
		JsGenerator.get()
				.addLine(getVarName() + ".setValue(\"" + text + "\");");
	}
}
