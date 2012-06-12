package de.ajaxgui.layout;

import de.ajaxgui.ControlContainer;
import de.ajaxgui.ext.JsGenerator;

public class FlowLayout extends ControlContainer {

	public FlowLayout() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxFlowLayout();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void setHorizontalSpacing(int hspace) {
		JsGenerator.get().addLine(
				getVarName() + ".setHorizontalSpacing(" + hspace + ");");
	}

	public void setVerticalSpacing(int vspace) {
		JsGenerator.get().addLine(
				getVarName() + ".setVerticalSpacing(" + vspace + ");");
	}
}
