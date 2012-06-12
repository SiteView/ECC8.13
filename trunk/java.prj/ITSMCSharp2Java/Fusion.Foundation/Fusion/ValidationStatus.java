package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:52
 */
public enum ValidationStatus {
	Committing,
	Done,
	DoneErrorsFound,
	DoneWarningsFound,
	DoneErrorsWarningsFound,
	FindingConflictsWithDb,
	FindingConflictsWithSystem,
	Validating
}