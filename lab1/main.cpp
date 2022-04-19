#include "iostream"

namespace iakov{

    struct point_t{

        double x_;

        double y_;
    };

    struct rectangle_t{

        double wight_;

        double height_;

        point_t center;
    };

    class IncorrectTriangle : public std::exception {

    public:

        IncorrectTriangle() : reason_("This triangle can't exist!") {}

        [[nodiscard]] const char * what() const override { return reason_; }

    private:

        const char * reason_;
    };

    class Shape{

    public:

        Shape() = default;

        virtual double getArea() = 0;

        virtual rectangle_t getFrameRect() = 0;

        virtual void move(double x, double y) = 0;

        virtual void move(point_t newCenter) = 0;

        virtual void scale(double mult) = 0;

        virtual void print() = 0;

        ~Shape() = default;
    };

    class Diamond : public Shape {
    private:

        point_t point1_{};
        point_t point2_{};
        point_t center_{};

        void setPoints(double x1, double y1, double x2, double y2){
            if (point1_.x_ == center_.x_) {
                point1_.x_ = x1;point1_.y_ = y1;
                point2_.x_ = x2;point2_.y_ = y2;
            } else {
                point1_.x_ = x2; point1_.y_ = y2;
                point2_.x_ = x1; point2_.y_ = y1;
            }
            try {
                if(isTriangleCorrect()) throw IncorrectTriangle();
            }catch (std::exception &error){
                std::cerr << std::endl << error.what() << std::endl;
                exit(1);
            }
        }

        [[nodiscard]] bool isTriangleCorrect() const{
            return point1_.x_ - center_.x_ + point2_.y_ - center_.y_ > sqrt(pow(point1_.x_ - center_.x_, 2) + pow(point2_.y_ - center_.y_, 2));
        };

    public:

        Diamond(double x1, double y1, double x2, double y2, double x3, double y3){
            if((x1 == x2 && y1 == y3) || (x1 == x3 && y1 == y2)){
                center_.x_ = x1; center_.y_ = y1;
                setPoints(x2, y2, x3, y3);
            }
            if((x2 == x3 && y2 == y1) || (x2 == x1 && y2 == y3)){
                center_.x_ = x2; center_.y_ = y2;
                setPoints(x1, y1, x3, y3);
            }
            if((x3 == x1 && y3 == y2) || (x3 == x2 && y3 == y1)){
                center_.x_ = x3; center_.y_ = y3;
                setPoints(x2, y2, x1, y1);
            }
            else{}
        }

        double getArea() override{
            return abs(point1_.x_ - center_.x_ )* abs(point2_.y_ - center_.y_) * 2;
        }

        rectangle_t getFrameRect() override{
            return rectangle_t{abs(point1_.x_ - center_.x_)*2, abs(point2_.y_ - center_.y_)*2, point_t{center_.x_, center_.y_}};
        }

        void move(double x, double y) override{
            center_.x_ += x; center_.y_ += y;
            point1_.x_ += x; point1_.y_ += y;
            point2_.x_ += x; point2_.y_ += y;
        }

        void move(point_t newCenter) override{
            double x = newCenter.x_ - center_.x_;
            double y = newCenter.y_ - center_.y_;
            move(x,y);
        }

        void scale(double mult) override{
            mult--;
            point1_.x_ += (point1_.x_ - center_.x_) * mult;
            point2_.y_ += (point2_.y_ - center_.y_) * mult;
        }

        void print() override{
            point_t point3{ center_.x_ + (point1_.x_ - center_.x_)*-1 , point1_.y_};
            point_t point4{  point2_.x_, center_.y_ + (point2_.y_ - center_.y_)*-1 ,};
            std::cout << "DIAMOND: " << point1_.x_ << " " << point1_.y_ <<
                      "; " << point2_.x_ << " " << point2_.y_ <<
                      "; " << point3.x_ << " " << point3.y_ <<
                      "; " << point4.x_ << " " << point4.y_ << ";\n";
        };

        ~Diamond() = default;
    };

    class Rectangle : public Shape {
    private:
        point_t point1_{};
        point_t point2_{};
    public:

        explicit Rectangle(double left, double down, double right, double top){
            point1_.x_ = std::min(left, right);
            point1_.y_ = std::min(down, top);
            point2_.x_ = std::max(left, right);
            point2_.y_ = std::max(down, top);
        }

        double getArea() override{
            return (std::max(point1_.x_, point2_.x_) - std::min(point1_.x_, point2_.x_)) * (std::max(point1_.y_, point2_.y_) - std::min(point1_.y_, point2_.y_));
        }

        rectangle_t getFrameRect() override {
            return rectangle_t{point2_.x_ - point1_.x_,
                               point2_.y_ - point1_.y_,
                               point_t{(point1_.x_ + point2_.x_)/2, (point1_.y_ + point2_.y_)/2}};
        };

        void move(double x, double y) override {
            point1_.x_ +=  x; point1_.y_ += y;
            point2_.x_ +=  x; point2_.y_ += y;
        }

        void move(point_t newCenter) override {
            double x = newCenter.x_ - ((point2_.x_ + point1_.x_)/2);
            double y = newCenter.y_ - ((point2_.y_ + point1_.y_)/2);
            move(x,y);
        }

        void scale(double mult) override {
            double wight = point2_.x_ - point1_.x_;
            double height = point2_.y_ - point1_.y_;
            mult--;
            point1_.x_ = point1_.x_ - wight*mult/2; point1_.y_ = point1_.y_ - height*mult/2;
            point2_.x_ = point2_.x_ + wight*mult/2; point2_.y_ = point2_.y_ + height*mult/2;
        }

        void print() override {
            std::cout << "RECTANGLE: " << point1_.x_ << " " << point1_.y_ << "; " << point2_.x_ << " " << point2_.y_ << ";\n";
        }

        ~Rectangle() = default;
    };

    class Triangle : public Shape{
    private:

        point_t point1_{};
        point_t point2_{};
        point_t point3_{};

        [[nodiscard]] bool isTriangleCorrect() const{

            double side1 = std::sqrt(std::pow(point1_.x_-point2_.x_, 2) + std::pow(point1_.y_-point2_.y_, 2));
            double side2 = std::sqrt(std::pow(point2_.x_-point3_.x_, 2) + std::pow(point2_.y_-point3_.y_, 2));
            double side3 = std::sqrt(std::pow(point1_.x_-point3_.x_, 2) + std::pow(point1_.y_-point3_.y_, 2));

            return std::min(side1, std::min(side2,side3))
                   + (side3 + side2 + side1 - std::max(side1, std::max(side2,side3))) > std::max(side1, std::max(side2,side3));
        }

    public:

        Triangle(double x1, double y1, double x2, double y2, double x3, double y3){

            point1_.x_ = x1;point1_.y_ = y1;
            point2_.x_ = x2;point2_.y_ = y2;
            point3_.x_ = x3;point3_.y_ = y3;

            try {
                if(!isTriangleCorrect()) throw IncorrectTriangle();
            }catch (std::exception &error){
                std::cerr << std::endl << error.what() << std::endl;
                exit(1);
            }
        };

        double getArea() override{
            return abs((point2_.x_ - point1_.x_) * (point3_.y_ - point1_.y_) - (point2_.y_ - point1_.y_) * (point3_.x_ - point1_.x_))/2;
        }

        rectangle_t getFrameRect() override {
            return rectangle_t{std::max(point1_.x_, std::max(point2_.x_, point3_.x_)) - std::min(point1_.x_, std::min(point2_.x_, point3_.x_)),
                               std::max(point1_.y_, std::max(point2_.y_, point3_.y_)) - std::min(point1_.y_, std::min(point2_.y_, point3_.y_)),
                               {(point3_.x_ + point2_.x_ + point1_.x_)/3, (point3_.y_ + point2_.y_ + point1_.y_)/3}
            };
        }

        void move(double x, double y) override{
            point1_.x_ += x; point1_.y_ += y;
            point2_.x_ += x; point2_.y_ += y;
            point3_.x_ += x; point3_.y_ += y;
        }
        void move(point_t newCenter) override {
            double x = newCenter.x_ - (point3_.x_ + point2_.x_ + point1_.x_)/3;
            double y = newCenter.y_ - (point3_.y_ + point2_.y_ + point1_.y_)/3;
            move(x,y);
        }

        void scale(double mult) override{
            double x = (point3_.x_ + point2_.x_ + point1_.x_)/3;
            double y = (point3_.y_ + point2_.y_ + point1_.y_)/3;
            mult = (mult-1);
            point1_.x_ += (point1_.x_ - x)*mult; point1_.y_ += (point1_.y_ - y)*mult;
            point2_.x_ += (point2_.x_ - x)*mult; point2_.y_ += (point2_.y_ - y)*mult;
            point3_.x_ += (point3_.x_ - x)*mult; point3_.y_ += (point3_.y_ - y)*mult;
        }

        void print() override{
            std::cout << "TRIANGLE: " << point1_.x_ << " " << point1_.y_ << "; "
                      << point2_.x_ << " " << point2_.y_ << "; "
                      << point3_.x_ << " " << point3_.y_ << ";\n";
        }

        ~Triangle() = default;
    };
}

void testShape(const std::shared_ptr<iakov::Shape>& shape);

int main(){

    std::shared_ptr<iakov::Rectangle> rectangle(new iakov::Rectangle(1,1,2,2));

    testShape(rectangle);

    std::cout << "\n";

    std::shared_ptr<iakov::Triangle> triangle(new iakov::Triangle(1,40,423,4,10,-10));

    testShape(triangle);

    std::cout << "\n";

    std::shared_ptr<iakov::Diamond> diamond(new iakov::Diamond(1,1,2,2,2,1));

    testShape(diamond);
    return 0;
}

void testShape(const std::shared_ptr<iakov::Shape>& shape){
    shape->print();
    std::cout << "Area: " << shape->getArea() << "\n";
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->move(1,1);
    std::cout << "Move x: 1, y: 1 : \n";
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Move to point 0,0 : \n";
    shape->move({0, 0});
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Scale 2 : \n";
    shape->scale(2);
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Scale 0.5 : \n";
    shape->scale(0.5);
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
}
