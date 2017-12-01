/*

  *  CBitmap.cpp

  *  CBitmap

  *

  *  Created by Le Gal on 24/10/06.

  *  Copyright 2006 ENSEIRB. All rights reserved.

  *

  */

#include "CBitmap.h"


  CBitmap::CBitmap(){
//        cout << "Creating a CBitmap()" << endl;
    bfType          = 19778;
    bfReserved1     = 0;
    bfReserved2     = 0;
    bfOffBits       = 54;
    biSize          = 40;
    biPlanes        = 1;
    biBitCount      = 24;
    biCompression   = 0;
    biXPelsPerMeter = 2835;
    biYPelsPerMeter = 2835;
    biClrUsed       = 0;
    biClrImportant  = 0;
}


CImage* CBitmap::getImage(){
    return image;
}



void CBitmap::setImage(CImage* _image){
    image       = _image;
    biHeight    = _image->size();
    biWidth     = _image->getLigne(0)->size();
    biSizeImage = biHeight * biWidth * biBitCount / 8;
    bfSize      = 54 + biSizeImage;
}



bool CBitmap::LoadBMP(string name){
//    cout << "Starting picture loading..." << endl;
    ifstream myfile ( name.c_str(), ios::in | ios::binary );
    if (myfile.is_open()){
        myfile.read((char*)(&bfType), 2);
        myfile.read((char*)(&bfSize), 4);
        myfile.read((char*)(&bfReserved1), 2);
        myfile.read((char*)(&bfReserved2), 2);
        myfile.read((char*)(&bfOffBits), 4);
        myfile.read((char*)(&biSize), 4);
        myfile.read((char*)(&biWidth), 4);
        myfile.read((char*)(&biHeight), 4);
        myfile.read((char*)(&biPlanes), 2);
        myfile.read((char*)(&biBitCount), 2);
        myfile.read((char*)(&biCompression), 4);
        myfile.read((char*)(&biSizeImage), 4);
        myfile.read((char*)(&biXPelsPerMeter), 4);
        myfile.read((char*)(&biYPelsPerMeter), 4);
        myfile.read((char*)(&biClrUsed), 4);
        myfile.read((char*)(&biClrImportant), 4);

        char t[4];
        int inverted = 0;//(biHeight < 0);
        biHeight     = abs( biHeight );
        biWidth      = abs( biWidth  );
        image        = new CImage(biHeight, biWidth);

        int lectures = 0;
        for(int y=0; y<biHeight; y++){
            for(int x=0; x<biWidth; x++){
                lectures += 3;

                CPixel *p = image->getLigne(y)->getPixel(x);
                if( inverted == true ){
                    p = image->getLigne(biHeight-y-1)->getPixel(x);
                }
                                //cout << "Tagging pixel (" << y << ", " << x << ")" << endl;
                t[0] = myfile.get();
                t[1] = myfile.get();
                t[2] = myfile.get();
                p->RGB((unsigned char)t[2], (unsigned char)t[1], (unsigned char)t[0]);
            }



                        /* On doit gerer le cas ou la largeur n'est pas un multiple de 4... */
            if( biWidth%4 != 0){
                for(int x=0; x<biWidth%4; x++){
                    t[0]= myfile.get();
                    cout << "Lecture d'un octet de bourage (ligne%4 != 0);" << endl;
                }
            }
                        /* Fin de la gestion des lignes de taille non modulo 4 */
        }

        cout << "Nombre de pixels lus : " << lectures << endl;
        int nombre = 0;
        while(myfile.eof() == false){
            nombre++;
            myfile.get();
        }
        cout << "Position dans le fichier : " << myfile.tellg() << endl;
        cout << "Nombre de donnes  lire : " << biSizeImage << endl;
        cout << "Nombre de donnes lues   : " << lectures << " (" << 3*(biHeight)*(biWidth)+54 << ")" << endl;
        cout << "Il restait " << nombre << " donnes  lire !" << endl;
    }else{
        cout << "Warning, unable to open the file : " << name << endl;
        return false;
    }

    return true;
}


bool CBitmap::SaveBMP(string name){
    cout << "Starting picture saving..." << endl;
    ofstream myfile ( name.c_str(), ios::out | ios::binary  );
    if (myfile.is_open()){
        myfile.write((char*)(&bfType), 2);
        myfile.write((char*)(&bfSize), 4);
        myfile.write((char*)(&bfReserved1), 2);
        myfile.write((char*)(&bfReserved2), 2);
        myfile.write((char*)(&bfOffBits), 4);
        myfile.write((char*)(&biSize), 4);
        myfile.write((char*)(&biWidth), 4);
        myfile.write((char*)(&biHeight), 4);
        myfile.write((char*)(&biPlanes), 2);
        myfile.write((char*)(&biBitCount), 2);
        myfile.write((char*)(&biCompression), 4);
        myfile.write((char*)(&biSizeImage), 4);
        myfile.write((char*)(&biXPelsPerMeter), 4);
        myfile.write((char*)(&biYPelsPerMeter), 4);
        myfile.write((char*)(&biClrUsed), 4);
        myfile.write((char*)(&biClrImportant), 4);

                /* On va maintenant creer l'image  proprement parler ... */
        char t[3];
        for(int y=0; y<biHeight; y++){
          CLigne *ligne = image->getLigne(/*image->size()-y-1*/y);
          for(int x=0; x<biWidth; x++){
                            //CPixel *p = image->getLigne(y)->getPixel(x);
            CPixel *p = ligne->getPixel(x);
            t[0]= p->Blue();
            t[1]= p->Green();
            t[2]= p->Red();
            myfile.write(t, 3);
        }

                        /* On doit gerer le cas ou la largeur n'est pas un multiple de 4...  */
        if( biWidth%4 != 0){
            cout << " largeur n'est pas multiple de 4 : " << biWidth << endl;
            for(int x=0; x<(biWidth%4); x++){
                t[0]= 0; t[1]= 0; t[2]= 0;
                myfile.write(t, 1);
                cout << "  Ecriture d'un byte de bourage (colonne%4 != 0);" << endl;
            }
        }
                        /* Fin de la gestion des lignes de taille non modulo 4 */
    }
    myfile.close();
}else{
    cout << "Warning, unable to open the file : " << name << endl;
    return false;
}
cout << "Picture saving finished !" << endl;
return true;
}


void CBitmap::dump(){

    cout << "bfType          : " << bfType << endl;

    cout << "bfSize          : " << bfSize << endl;

    cout << "bfReserved1     : " << bfReserved1 << endl;

    cout << "bfReserved2     : " << bfReserved2 << endl;

    cout << "bfOffBits       : " << bfOffBits << endl;

    cout << "biSize          : " << biSize << endl;

    cout << "biWidth         : " << biWidth << endl;

    cout << "biHeight        : " << biHeight << endl;

    cout << "biPlanes        : " << biPlanes << endl;

    cout << "biBitCount      : " << biBitCount << endl;

    cout << "biCompression   : " << biCompression << endl;

    cout << "biSizeImage     : " << biSizeImage << endl;

    cout << "biXPelsPerMeter : " << biXPelsPerMeter << endl;

    cout << "biYPelsPerMeter : " << biYPelsPerMeter << endl;

    cout << "biClrUsed       : " << biClrUsed << endl;

    cout << "biClrImportant  : " << biClrImportant << endl;

}








