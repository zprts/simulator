#ifndef CAMERASCONTAINER_H
#define CAMERASCONTAINER_H

#include "camera.h"
#include <QMutex>
#include <QTableWidget>

/**
 * @brief Singleton stanowiący zbiór wszsytkich kamer
 */
class CamerasContainer
{
public:
	/**
	 * @brief Funkcja zwraca jedyną instancję obiektu tej klasy.
	 * @return Instancja obiektu klasy CamerasContainer.
	 */
	static CamerasContainer &getInstance() {
		static CamerasContainer c;
		return c;
	}
	QVector<Camera> cameras_; //!< Wektor kamer
	int				currentCam = -1; //!< Zmienna opisująca aktualną kamerę
	/**
	 * @brief Funkcja blokująca dostęp do kontenera kamer
	 */
	void use() {
		m_.lock();
	}
	/**
	 * @brief Funkcja odblokowuje dostęp do kontenera kamer
	 */
	void free() {
		m_.unlock();
	}
	/**
	 * @brief Funkcja sprawdza czy aktualnie aktywna kamera jest poprawna (czy istnieje w zbiorze)
	 * @return True jeśli kamera jest poprawna.
	 */
	bool currentCamValid() {
		if (currentCam < 0)
			return false;
		return true;
	}
	/**
	 * @brief Funkcja zwraca wskaźnik do aktualnej kamery. Przed użyciem należy wykonać funkcję currentCamValid()
	 * @return Wskaźnik do obiektu Camera
	 */
	Camera *getCurrentCam() {
		return &cameras_[currentCam];
	}
	/**
	 * @brief Funkcja generuje odpowiedni zestaw zakładek opisujących kamery
	 * @param w Wskaźnik do obiektu zakładek
	 */
	void genTab(QTabWidget *w);
private:
	/**
	 * @brief Mutex do kontroli dostępu
	 * @see use() free()
	 */
	QMutex	m_;
	CamerasContainer() {}
};

#endif // CAMERASCONTAINER_H
