package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;



public class TreeFile extends Control{
	private String text = null;
	public TreeFile(String text,String icon) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTreeFile(\"" + text + "\",\"" + icon + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}
	public String getText() {
		return text;
	}
	private Control parent = null;
	public Control getParent() {
		return parent;
	}
	public void setParent(Control parent) {
		this.parent = parent;
	}
}