package de.ajaxgui;

import java.util.ArrayList;

import de.ajaxgui.ext.JsGenerator;

public class TabControl extends Control {

	protected TabPage selected = null;

	private ArrayList<TabPage> tabPages = new ArrayList<TabPage>();

	public TabControl() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTabView();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void add(TabPage tp) {
		tabPages.add(tp);
		tp.control = this;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".getBar().add(" + tp.getVarName() + ");");
		jg.addLine(getVarName() + ".getPane().add(" + tp.getVarName()
				+ ".getPage());");
		if (selected == null)
			setSelected(tp);
	}

	public TabPage getSelected() {
		return selected;
	}

	public void setSelected(TabPage selected) {
		this.selected = selected;
		JsGenerator.get().addLine(selected.getVarName() + ".setChecked(true);");
	}
}
