#include <opencv2/opencv.hpp>

int main() {
        cv::VideoCapture rep;
        int ch;
        std::cout << "1. Load video\n2. Track people from webcam\n";
        std::cin >> ch;
        if (ch == 1) {
            std::string vlocation;
            std::cout << "Provide the location of the video: ";
            std::cin >> vlocation;
            rep.open(vlocation);
        }
        else if (ch == 2) {
            rep.open(0);
        }
        else {
            std::cout << "Invalid option.\n";
            return 1;
        }
        if (!rep.isOpened()) {
            std::cerr << "Error: Unable to open the video source.\n";
            return 1;
        }
        cv::CascadeClassifier fullbody;
        cv::CascadeClassifier upperbody;
        if (!upperbody.load(cv::samples::findFile("C:\\Users\\patri\\Downloads\\ai proj\\opencv\\sources\\data\\haarcascades\\haarcascade_upperbody.xml"))) {
            std::cerr << "Error: Unable to load the face cascade classifier.\n";
            return 1;
        }
        if (!fullbody.load(cv::samples::findFile("C:\\Users\\patri\\Downloads\\ai proj\\opencv\\sources\\data\\haarcascades\\haarcascade_fullbody.xml"))) {
            std::cerr << "Error: Unable to load the person cascade classifier.\n";
            return 1;
        }
        cv::Mat frame;
        while (rep.read(frame)) {
            if (frame.empty()) {
                break;
            }

            std::vector<cv::Rect> persons;
            fullbody.detectMultiScale(frame, persons, 1.1, 3, 0, cv::Size(30, 30));

            for (const auto& person : persons) {
                cv::rectangle(frame, person, cv::Scalar(0, 255, 0), 2);
            }

            cv::imshow("Person Detection", frame);

            if (cv::waitKey(30) == 27) {
                break;
            }
        }
        rep.release();
        cv::destroyAllWindows();
    return 0;
}
