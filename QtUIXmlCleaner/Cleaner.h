#ifndef _QTUIXMLCLEANER_CLEANER_H_
#define _QTUIXMLCLEANER_CLEANER_H_

#include <QThread>
#include <QException>

class QString;

namespace QtXMLCleaner {

	enum class SortType {
		ALPHABETICAL,
		NUMERICAL
	};

	enum class SortOrder {
		ASCENDING,
		DESCENDING
	};

	class Cleaner : public QThread {

		Q_OBJECT

	public:
		Cleaner(const QString& infile, const QString& outfile);
		~Cleaner() = default;
		void SetSortQGridLayoutChildren(bool newValue);
		void SetRemoveStdsetZero(bool newValue);
		void SetRemoveNativeTrue(bool newValue);

		///  The QThread run function: everything in this function is on its own thread
		void run() override;

	signals:
		void processComplete();
		void errorOccurred(QString message);

	private:

		void RemoveNativeTrue(std::string &line) const;
		void RemoveStdsetZero(std::string &line) const;
		void SortQGridLayoutChildren(const std::string &line, std::istream &is) const;

		typedef std::vector<std::tuple<QString, SortType, SortOrder>> SortPredicateConfiguration;

		//void SortChildren(const SortPredicateConfiguration &sortOrder) const;

		bool _sortQGridLayoutChildren = true;
		bool _removeStdsetZero = true;
		bool _removeNativeTrue = true;

		QString _infile;
		QString _outfile;
	};

}

#endif // _QTUIXMLCLEANER_CLEANER_H_