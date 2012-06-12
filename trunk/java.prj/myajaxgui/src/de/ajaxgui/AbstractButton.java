package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import de.ajaxgui.ext.JsGenerator;

public abstract class AbstractButton extends Control {
	protected ArrayList<String> clickFunc = new ArrayList<String>();

	protected ArrayList<Object> clickObject = new ArrayList<Object>();

	private String text = "";

	public AbstractButton(String text) {
		this.text = text;
	}

	protected void addClick(Object o, String func) {
		clickObject.add(o);
		clickFunc.add(func);
		JsGenerator
				.get()
				.addLine(
						getVarName()
								+ ".addEventListener(QxConst.EVENT_TYPE_CLICK, clickEvent);");
	}

	public void doClick() {
		for (int i = 0; i < clickObject.size(); i++) {
			Object obj = clickObject.get(i);
			String func = clickFunc.get(i);
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

	public void setText(String text) {
		this.text = text;
		JsGenerator.get()
				.addLine(getVarName() + ".setLabel(\"" + text + "\");");
	}
}
