// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 16/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;

namespace seneca {

	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {

		Utilities utility;
		string str;
		size_t nextPos;
		bool more = false;
		string item;
		string nextItem;

		ifstream fs(file);
		if (!fs) {
			throw std::string("Unable to open file");
		}

		while (getline(fs, str)){
			nextPos = 0;
			more = true;
			Workstation* currentStation{};
			Workstation* nextStation{};
			string item;
			string nextItem;

			item = utility.extractToken(str, nextPos, more);
			currentStation = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
				return ws->getItemName() == item;
			});
			m_activeLine.push_back(currentStation);


			if (more != false) {
				nextItem = utility.extractToken(str, nextPos, more);
				nextStation = *find_if(stations.begin(), stations.end(), [&](Workstation* s) {
					return s->getItemName() == nextItem;
					});
				currentStation->setNextStation(nextStation);
			}
		}

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1) {
			auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws2) {
				return ws1 == ws2->getNextStation();
				});
			if (firstStation == m_activeLine.end()) {
				m_firstStation = ws1;
			}
			});

		fs.close();
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations() {

		m_activeLine.clear();
		Workstation* ws;
		m_activeLine.push_back(m_firstStation);
		while ((ws = m_activeLine.back()->getNextStation())) {
			m_activeLine.push_back(ws);
		}
	}

	bool LineManager::run(std::ostream& os) {
		static size_t count;
		count++;

		os << "Line Manager Iteration: " << count << endl;

		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& i : m_activeLine) {
			i->fill(os);
		}
		for (auto& i : m_activeLine) {
			i->attemptToMoveOrder();
		}

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}

	void LineManager::display(std::ostream& os) const {
		for ( size_t i = 0; i < m_activeLine.size(); i++) {
			m_activeLine[i]->display(os);
		}
	}

}

