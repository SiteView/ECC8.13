package de.ajaxgui;

import java.util.ArrayList;

import de.ajaxgui.ext.JsGenerator;

public class ExtTabControl extends Control {

	protected ExtTabPage selected = null;

	private ArrayList<ExtTabPage> extTabPages = new ArrayList<ExtTabPage>();

	public ExtTabControl() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxBarView();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName() + ".setBarPosition(\"left\");");
		jg.addLine(getVarName()
				+ ".getBar().setVerticalChildrenAlign(\"middle\");");
	}

	public void add(ExtTabPage etp) {
		extTabPages.add(etp);
		etp.control = this;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".getBar().add(" + etp.getVarName() + ");");
		jg.addLine(getVarName() + ".getPane().add(" + etp.getVarName()
				+ ".getPage());");
		if (selected == null)
			setSelected(etp);
	}

	public ExtTabPage getSelected() {
		return selected;
	}

	public void setSelected(ExtTabPage selected) {
		this.selected = selected;
		JsGenerator.get().addLine(selected.getVarName() + ".setChecked(true);");
	}
}
