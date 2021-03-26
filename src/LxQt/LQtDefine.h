#ifndef LQTDEFINE_H
#define LQTDEFINE_H

#endif // LQTDEFINE_H

#ifdef DEBUG_VAR
#undef DEBUG_VAR
#endif
#define DEBUG_VAR(VAR) qDebug() << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << #VAR << ":" <<  VAR;
