//
// Created by Admin on 2023/5/23.
//

#ifndef UNTITLED9_OPENMACHINEFEE_H
#define UNTITLED9_OPENMACHINEFEE_H
class OpenMachineFee
{
public:
    double printPrince;
    double paperPrice;
    double surfPrice;
    double biePrice;
    double dieCutPrice;
    double nianPriceTotall;
    double totallPrice;
    double width;
    double height;

    OpenMachineFee( double printP, double paperP, double surfP,
                    double bieP, double dieCutP, double nianPt, double totalP, double W , double H  )
    {
        printPrince = printP;
        paperPrice = paperP;
        surfPrice = surfP;
        biePrice = bieP;
        dieCutPrice = dieCutP;
        nianPriceTotall = nianPt;
        totallPrice = totalP;
        width = W;
        height = H;
    }
    void setPrintPrice ( double printP)
    {
        printPrince = printP;
    }

    void setPaperPrice( double paperP )
    {
        paperPrice = paperP;
    }

    void setSurfPrice( double surfP )
    {
        surfPrice = surfP;
    }

    void setBiePrice( double bieP )
    {
        biePrice = bieP;
    }

    void setDieCutPrice( double dieCutP )
    {
        dieCutPrice = dieCutP;
    }
    void setNianPriceTotal( double nianPt )
    {
        nianPriceTotall = nianPt;
    }
    void setTotalPrice( double totalP)
    {
        totallPrice = totalP;
    }
    double getHeight()
    {
        return height;
    }
    double getWidth()
    {
        return width;
    }

};


#endif //UNTITLED9_OPENMACHINEFEE_H
