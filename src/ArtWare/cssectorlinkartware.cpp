#include "cssectorlinkartware.h"


namespace cs
{


CSSectorLinkArtWare::CSSectorLinkArtWare(Type t, QWidget *parent)
    : cs::CSArtWare(parent)
{
    setType(t);
    setTextColor(Qt::black);
}

void CSSectorLinkArtWare::setText(const QString &txt)
{
    _txt = txt;

    auto r = calcTextRect();
    update(r);
}

void CSSectorLinkArtWare::setTextColor(const QColor &color)
{
    _txtColor = color;
    update();
}

QString CSSectorLinkArtWare::text() const
{
    return _txt;
}

QColor CSSectorLinkArtWare::textColor() const
{
    return _txtColor;
}

CSSectorLinkArtWare::Type CSSectorLinkArtWare::type() const
{
    return _type;
}

void CSSectorLinkArtWare::drawAll(QPainter &p)
{
    drawImage(p);
    drawText(p);
}

void CSSectorLinkArtWare::drawImage(QPainter &p)
{
    auto r = calcImageRect();

    p.save();
    scalePainter(p);
    p.drawPixmap(r, _pix);
    p.restore();
}

void CSSectorLinkArtWare::drawText(QPainter &p)
{
    auto r = calcTextRect();
    auto f = font();
    f.setPixelSize(14);

    p.save();
    scalePainter(p);
    p.setPen(_txtColor);
    p.setFont(f);
    p.drawText(r, Qt::AlignCenter, _txt);
    p.restore();
}

void CSSectorLinkArtWare::setType(Type type)
{
    _type = type;
    updatePixmap();
}

/**
 * @brief Reload the pixmap
 */
void CSSectorLinkArtWare::updatePixmap()
{
    switch (_type)
    {
    case Down:
        _pix = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
                    "89504e470d0a1a0a0000000d4948445200000028000000280806000001fbf988fb000000017352474200aece1ce90000004465584966"
                    "4d4d002a00000008000187690004000000010000001a000000000003a00100030000000100010000a00200040000000100000028a003"
                    "00040000000100000028000000007ae666ac000002dd494441545809ed98bf6b144114c773d12b2246459144211a2cb4957416fe00b1"
                    "0944ed2cb489e9042d2c0c36827f44c04acec64e449b345a06c152888d2288450a490a0583868bf97cf7668699bdd9cdeeed9233780f"
                    "bef766def73b6fdeccce4e2e373494677f31f1b8d14447e3a0093c976f984ea2525b36dc71653fc97d2a734c033698a48169a28f9943"
                    "7a2298655a03f18f8204049e824c9338ba1b411689b074ac5f7d56330adcb66b75b616f714898d53f34f883991f4a7a38b80b824818c"
                    "7672403abdce67e1ed7153fba363edfa85b159fea118dbda02b23503b55b854b44bc4f62fc5e3b88f602b0b6e0c59dc6c69c473d012e"
                    "80d3e0a6234c83d82d211df7fbc17b80f800e4315f50a0dde6287eb63a979064ee205bb28cb7e7bbf0012b9abcf684ee09a96456fd84"
                    "4a8e17adc6e8daf83b25c70ce45576800735097e01d9a78e4bfa93b1bcee29c74806bf26bec10148de6d5f03f70234e1aefaf1ae36a2"
                    "bb3648fb84daf831f003c8e4c74c3ce1ad3eea112fa609625ffd58baef73c19b82f0bd48fc1b5fc4b24e9af892bcedfb9acc36c99e65"
                    "9170db5e20eeb65112f467b292e5c4bf50f14617afd92bd8759b30d8431becc1dfb663ea4a68f3f5fa5dd18def6afc3f152edbb5fb97"
                    "c379820f2c51c22f730e1f96d00fa4bb7c0782cbabea5ab8ab46c871199c03fa0e7718ac8115f00ebce580ade377c62868183c06bfc1"
                    "1fd002d7c07ebf02f54d5cbc74d26b5ced17899b97e4b3a00de65dd0348835c114b8627c33a29987d3f8d93457ba4f9245309e37105e"
                    "05ad00d92b701fcc18afbe4cfc545e9ec21c892e82b31a804f0ac48f807b5949e0f66471264fbd8f94098f8225f00d7c00337905580e"
                    "9dbea8af02997cad2fa39da7b2a7b089ca49d209487a08bc049b60a76c9d89a27fdfbab61ee12a45ebfeea87b5b82783b73a7668fb55"
                    "9c36e4487a576205a6357ded0f0aacbafdb11ddcac9ab4c278fd601158acc01b28b6fd1f2ec8524fe73b6906bfa6d4b397bb29cb16d5"
                    "c7a923c5275c480000000049454e44ae426082")));
        break;
    case Up:
        _pix = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
                    "89504e470d0a1a0a0000000d4948445200000028000000280806000001fbf988fb000000017352474200aece1ce90000004465584966"
                    "4d4d002a00000008000187690004000000010000001a000000000003a00100030000000100010000a00200040000000100000028a003"
                    "00040000000100000028000000007ae666ac000002d4494441545809ed98bf6b544110c773d12b0c46458544410936826548a3200822"
                    "48c01f9d0836d1ced2c260235afa0704ace42a3b1145b0d24ec4c62e5a2882550a490a0583868b7ebe2f3bcbfbb17becf39d397fdcc0"
                    "37b333df99d9d97dfb368f1b19e9253f10f1a8f1421c8efb72b4f4c7a234968c6ea8ba7f2973289ad32a4fd24234d19b684a3241e98b"
                    "e08412d0b34edf94f602710f444581c1ddf015dc408d977d83b259cd38f0dbaed5592fd953c4de0966e8f90bc41591d8b3c14540f853"
                    "c2383b20564d3a797bb2a9f399b171ff036333fd217eb6b503242b0e1a7792da23b00d8e2818bdd592182f0093859cdfc798afa2c99a"
                    "ac3871e0bf248438f315de03827740ec33325177398aef2dd617a4983fc846d6d176be930f586af1be17f44f482db3eabb74b23fb51b"
                    "17d7455fad99330c6fb2033ca829f01548de6da8cc9e0ad5f54f394492fc18ff1a0760acccc33d006db8b365ae601374cb1c8c0f6a8c"
                    "9e009f81447ac2f933dee22b9ac0e7e029789527b13ff6b2f35c65ac8215a773c0bd8871e60fbd7aaf8d0ce863015fc1e56f1b79e9e0"
                    "70814d333ef060d62aa1146b22e7ad6068c9c6d5d1972db85f05addeaf7e2bfafccae0ffe970d1d69ebf1c8ee3bc6e440dbdc839bc51"
                    "237e18fa97ef40e1f26aba162eab6dd438098e027dc3ed062b6009bc04cf3860abe8cd111a1a05b7c137f01d74c039b03ddf816ce717"
                    "af38c52bafef17899f97e273a00be6bdd30df0e91b7d1a9c72ba1d88998753fe5c994bb6491e034fc032780b6662c9706a6809481e81"
                    "6be08cd3b225e2a763356af929a4e2a79584d677c424d80beec40ac16d8971aeceef79a44c9c35d86bf23c47bc3ed4b5eb12e9bebe8c"
                    "f9b91a8d69ec40a302a1648aee020fc13ad82c5965a2e0ffb7cad613b84ce3babf06211deec9c25b1d3ab4836a4e1bb2a7bc2ba106cb"
                    "3103b5870d36ddfed00eae372dda205f3f581424d4e005221afd08549821ddf844e8f0d794f4fdfa57227f02c770a61e1d1cf5110000"
                    "000049454e44ae426082")));
        break;
    }

    update();
}

QRect CSSectorLinkArtWare::calcImageRect() const
{
    return QRect(0, 0, _sizeOrg.width(), _sizeOrg.height());
}

QRect CSSectorLinkArtWare::calcTextRect() const
{
    return QRect(0, _sizeOrg.height()/2, _sizeOrg.width(), _sizeOrg.height()/2-6);
}


}   // `cs`
