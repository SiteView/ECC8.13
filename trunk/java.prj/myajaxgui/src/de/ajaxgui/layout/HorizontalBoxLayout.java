package de.ajaxgui.layout;

import de.ajaxgui.Control;
import de.ajaxgui.ControlContainer;
import de.ajaxgui.ext.JsGenerator;

public class HorizontalBoxLayout extends ControlContainer {
	public static enum Alignment {
		LEFT, CENTER, RIGHT
	}

	public HorizontalBoxLayout() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxHorizontalBoxLayout();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void add(Control control, int xFactor) {
		super.add(control);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(control.getVarName() + ".setWidth(\"" + xFactor + "*\");");
	}

	public void setSpacing(int space) {
		JsGenerator.get().addLine(getVarName() + ".setSpacing(" + space + ");");
	}

	public void setAlignment(HorizontalBoxLayout.Alignment alignment) {
		JsGenerator jg = JsGenerator.get();
		switch (alignment) {
		case LEFT:
			jg.addLine(getVarName() + ".setHorizontalChildrenAlign(\"left\");");
			break;
		case CENTER:
			jg.addLine(getVarName()
					+ ".setHorizontalChildrenAlign(\"center\");");
			break;
		case RIGHT:
			jg
					.addLine(getVarName()
							+ ".setHorizontalChildrenAlign(\"right\");");
			break;
		}
	}
}
