package de.ajaxgui.layout;

import de.ajaxgui.Control;
import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;

public class GridLayout extends Control {
	public static enum HorizontalAlignment {
		LEFT, CENTER, RIGHT
	}

	public static enum VerticalAlignment {
		TOP, MIDDLE, BOTTOM
	}

	public GridLayout(int rowCount, int columnCount) {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxGridLayout();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName() + ".setRowCount(" + rowCount + ");");
		jg.addLine(getVarName() + ".setColumnCount(" + columnCount + ");");
		jg.addLine(getVarName() + ".auto();");
	}

	public void setHorizontalSpacing(int hspace) {
		JsGenerator.get().addLine(
				getVarName() + ".setHorizontalSpacing(" + hspace + ");");
	}

	public void setVerticalSpacing(int vspace) {
		JsGenerator.get().addLine(
				getVarName() + ".setVerticalSpacing(" + vspace + ");");
	}

	public void setColumnWidth(int column, int width) {
		JsGenerator.get()
				.addLine(
						getVarName() + ".setColumnWidth(" + column + ","
								+ width + ");");
	}

	public void setRowHeight(int row, int height) {
		JsGenerator.get().addLine(
				getVarName() + ".setRowHeight(" + row + "," + height + ");");
	}

	public void mergeCells(int startCol, int startRow, int colLength,
			int rowLength) {
		JsGenerator.get().addLine(
				getVarName() + ".mergeCells(" + startCol + "," + startRow + ","
						+ colLength + "," + rowLength + ");");
	}

	public void add(Control control, int column, int row) {
		ComponentManager.get().addComponent(control);
		JsGenerator.get().addLine(
				this.getVarName() + ".add(" + control.getVarName() + ","
						+ column + "," + row + ");");
	}

	public void setColumnHorizontalAlignment(int column,
			GridLayout.HorizontalAlignment alignment) {
		JsGenerator jg = JsGenerator.get();
		switch (alignment) {
		case LEFT:
			jg.addLine(getVarName() + ".setColumnHorizontalAlignment(" + column
					+ ",\"left\");");
			break;
		case CENTER:
			jg.addLine(getVarName() + ".setColumnHorizontalAlignment(" + column
					+ ",\"center\");");
			break;
		case RIGHT:
			jg.addLine(getVarName() + ".setColumnHorizontalAlignment(" + column
					+ ",\"right\");");
			break;
		}
	}

	public void setColumnVerticalAlignment(int column,
			GridLayout.VerticalAlignment alignment) {
		JsGenerator jg = JsGenerator.get();
		switch (alignment) {
		case TOP:
			jg.addLine(getVarName() + ".setColumnVerticalAlignment(" + column
					+ ",\"top\");");
			break;
		case MIDDLE:
			jg.addLine(getVarName() + ".setColumnVerticalAlignment(" + column
					+ ",\"middle\");");
			break;
		case BOTTOM:
			jg.addLine(getVarName() + ".setColumnVerticalAlignment(" + column
					+ ",\"bottom\");");
			break;
		}
	}

	public void setRowHorizontalAlignment(int row,
			GridLayout.HorizontalAlignment alignment) {
		JsGenerator jg = JsGenerator.get();
		switch (alignment) {
		case LEFT:
			jg.addLine(getVarName() + ".setRowHorizontalAlignment(" + row
					+ ",\"left\");");
			break;
		case CENTER:
			jg.addLine(getVarName() + ".setRowHorizontalAlignment(" + row
					+ ",\"center\");");
			break;
		case RIGHT:
			jg.addLine(getVarName() + ".setRowHorizontalAlignment(" + row
					+ ",\"right\");");
			break;
		}
	}

	public void setRowVerticalAlignment(int row,
			GridLayout.VerticalAlignment alignment) {
		JsGenerator jg = JsGenerator.get();
		switch (alignment) {
		case TOP:
			jg.addLine(getVarName() + ".setRowVerticalAlignment(" + row
					+ ",\"top\");");
			break;
		case MIDDLE:
			jg.addLine(getVarName() + ".setRowVerticalAlignment(" + row
					+ ",\"middle\");");
			break;
		case BOTTOM:
			jg.addLine(getVarName() + ".setRowVerticalAlignment(" + row
					+ ",\"bottom\");");
			break;
		}
	}
}
