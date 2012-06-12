package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;



public class TreeFolder extends Control{
	private String text = null;
	public TreeFolder(String text,String icon1,String icon2) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTreeFolder(\"" + text + "\",\"" + icon1 + "\",\"" + icon2 + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName() + ".setBorder(QxBorderObject.presets.inset);");
	}
	public TreeFolder(String text,String icon) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTreeFolder(\"" + text + "\",\"" + icon + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		//jg.addLine(getVarName() + ".setBorder(QxBorderObject.presets.inset);");
	}
	public TreeFolder(String text) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTreeFolder(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		//jg.addLine(getVarName() + ".setBorder(QxBorderObject.presets.inset);");
	}
	public void add(TreeFile treefile){
		treefile.setParent(this);
		JsGenerator.get().addLine(getVarName() + ".add(" + treefile.getVarName() + ");");
	}
	
	public void add(TreeFile...treefiles){
		for (TreeFile treefile: treefiles)
			this.add(treefile);
	}
	public void add(TreeFolder treefolder){
		treefolder.setParent(this);
		JsGenerator.get().addLine(getVarName() + ".add(" + treefolder.getVarName() + ");");
	}
	
	public void add(TreeFolder...treefolders){
		for (TreeFolder treefolder: treefolders)
			this.add(treefolder);
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