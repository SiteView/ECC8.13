package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;

public class ComboBox extends Control {

	private ArrayList<ComboBoxItem> comboBoxItems = new ArrayList<ComboBoxItem>();

	public ComboBoxItem selected = null;

	private ArrayList<String> selectionChangedFunc = new ArrayList<String>();

	private ArrayList<Object> selectionChangedObject = new ArrayList<Object>();

	public ComboBox() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxComboBox();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg
				.addLine(getVarName()
						+ ".addEventListener(\"changeSelected\", selectionChangedEvent);");
	}

	public void add(ComboBoxItem cbi) {
		comboBoxItems.add(cbi);
		ComponentManager.get().addComponent(cbi);
		JsGenerator.get().addLine(
				getVarName() + ".add(" + cbi.getVarName() + ");");
	}

	public void addSelectionChanged(Object o, String func) {
		selectionChangedObject.add(o);
		selectionChangedFunc.add(func);
	}

	public void clear() {
		comboBoxItems.clear();
		selected = null;
		JsGenerator.get().add(getVarName() + ".removeAll();");
	}

	public void doSelectionChanged() {
		for (int i = 0; i < selectionChangedObject.size(); i++) {
			Object obj = selectionChangedObject.get(i);
			String func = selectionChangedFunc.get(i);
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

	public ComboBoxItem getSelected() {
		return selected;
	}

	public void setSelected(ComboBoxItem selected) {
		this.selected = selected;
		JsGenerator.get().addLine(
				getVarName() + ".setSelected(" + selected.getVarName() + ");");
	}
}
