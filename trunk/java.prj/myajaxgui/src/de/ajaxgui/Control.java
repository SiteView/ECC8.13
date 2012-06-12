package de.ajaxgui;

import de.ajaxgui.ext.Component;
import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;

public class Control extends Component {
	private boolean enabled = true;

	private int height = 0;

	private int left = 0;

	private int top = 0;

	private boolean visibility = true;

	private int width = 0;

	public Control() {
		ComponentManager cm = ComponentManager.get();
		cm.addComponent(this);
	}

	public boolean isEnabled() {
		return enabled;
	}

	public boolean isVisibility() {
		return visibility;
	}

	public void setDimension(int width, int height) {
		setWidth(width);
		setHeight(height);
	}

	public void setEnabled(boolean enabled) {
		this.enabled = enabled;
		if (enabled) {
			JsGenerator.get().addLine(getVarName() + ".setEnabled(true);");
		} else {
			JsGenerator.get().addLine(getVarName() + ".setEnabled(false);");
		}
	}

	public void setHeight(int height) {
		this.height = height;
		JsGenerator.get().addLine(getVarName() + ".setHeight(" + height + ");");
	}

	public void setLeft(int left) {
		this.left = left;
		JsGenerator.get().addLine(getVarName() + ".setLeft(" + left + ");");
	}

	public void setLocation(int left, int top) {
		setLeft(left);
		setTop(top);
	}

	public void setTop(int top) {
		this.top = top;
		JsGenerator.get().addLine(getVarName() + ".setTop(" + top + ");");
	}

	public void setVisibility(boolean visibility) {
		this.visibility = visibility;
		if (visibility) {
			JsGenerator.get().addLine(getVarName() + ".setVisibility(true);");
		} else {
			JsGenerator.get().addLine(getVarName() + ".setVisibility(false);");
		}
	}

	public void setWidth(int width) {
		this.width = width;
		JsGenerator.get().addLine(getVarName() + ".setWidth(" + width + ");");
	}

	public void setAllowStretchX(boolean bool) {
		if (bool)
			JsGenerator.get()
					.addLine(getVarName() + ".setAllowStretchX(true);");
		else
			JsGenerator.get().addLine(
					getVarName() + ".setAllowStretchX(false);");
	}

	public void setAllowStretchY(boolean bool) {
		if (bool)
			JsGenerator.get()
					.addLine(getVarName() + ".setAllowStretchY(true);");
		else
			JsGenerator.get().addLine(
					getVarName() + ".setAllowStretchY(false);");
	}

	public void setDrawBorder(boolean bool) {
		if (bool)
			JsGenerator
					.get()
					.addLine(
							getVarName()
									+ ".setBorder(QxBorderObject.presets.outset);");
		else
			JsGenerator.get().addLine(getVarName() + ".setBorder();");
	}

	public void setPadding(int padding) {
		JsGenerator.get().addLine(
				getVarName() + ".setPadding(" + padding + ");");
	}
}
