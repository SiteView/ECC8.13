package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import de.ajaxgui.ext.Component;
import de.ajaxgui.ext.JsGenerator;



public class Tree extends Control{
	private List<String> selectionChangedFunc = new ArrayList<String>();

	private List<Object> selectionChangedObject = new ArrayList<Object>();
	
	private String text = null;
	public Tree(String text) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTree(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName() + ".setBorder(QxBorderObject.presets.inset);");
		jg.addLine(getVarName()
				+ ".getManager().addEventListener(\"changeSelection\", treeSelectionChangedEvent);");
	}
	
	public String getText() {
		return text;
	}

	public void setBackgroundColor(int color){
		JsGenerator.get().addLine(getVarName() + ".setBackgroundColor(" + color + ");");
	}


	public void setBottom(int value){
		JsGenerator.get().addLine(getVarName() + ".setBottom(" + value + ");");
	}
	public void setOverflow(String value){
		JsGenerator.get().addLine(getVarName() + ".setOverflow(\"" + value + "\");");
	}
	
	public void add(TreeFolder treefolder){
		treefolder.setParent(this);
		JsGenerator.get().addLine(getVarName() + ".add(" + treefolder.getVarName() + ");");
	}
	public void addSelectionChanged(Object o, String func) {
		selectionChangedObject.add(o);
		selectionChangedFunc.add(func);
	}

	public void doSelectionChanged(Component component) {
		for (int i = 0; i < selectionChangedObject.size(); i++) {
			Object obj = selectionChangedObject.get(i);
			String func = selectionChangedFunc.get(i);
			Class cl = obj.getClass();
			Method m;
			try {
				m = cl.getMethod(func, new Class[] {Component.class});
				try {
					m.invoke(obj,component);
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