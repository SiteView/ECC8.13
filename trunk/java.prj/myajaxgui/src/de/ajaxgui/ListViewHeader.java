package de.ajaxgui;

import java.util.ArrayList;

import de.ajaxgui.ext.Component;
import de.ajaxgui.ext.JsGenerator;

public class ListViewHeader extends Component {

	public static int ColumnTypeText = 0;

	private ArrayList<String> columns = new ArrayList<String>();

	private ArrayList<Integer> columnTypes = new ArrayList<Integer>();

	public ListViewHeader() {
		JsGenerator.get().addLine(getVarName() + " = {};");
	}

	public void addColumn(String label, int width, int type) {
		columns.add(label);
		columnTypes.add(type);
		// JsGenerator.addLine(getVarName() + "." + label + " = {};");
		JsGenerator.get().addLine(
				getVarName() + "." + label + " = {label:\"" + label
						+ "\",width:" + width + ",type:\"text\"};");
		// JsGenerator.addLine(getVarName() + "." + label + ".label = \"" +
		// label
		// + "\";");
		// JsGenerator.addLine(getVarName() + "." + label + ".width = " + width
		// + ";");
		// JsGenerator.addLine(getVarName() + "." + label + ".type =
		// \"text\";");
	}

	protected ArrayList getColumns() {
		return columns;
	}

	protected ArrayList getColumnTypes() {
		return columnTypes;
	}
}
