
#include "common.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Sphere::intersect(vec4 p0_w, vec4 V_w){
  IntersectionValues result;
  //TODO: Ray-sphere setup

  vec4 p0_o = INVC * p0_w;
  vec4 V_o = INVCStar * V_w;
  double len = length(V_o);

  V_o = normalize(V_o);
  double t_o = raySphereIntersection(p0_o, V_o);
  result.t_w = t_o / len;


  //To shade we need to find the intersection point in world space and the normal in world space
  result.P_w = p0_w + result.t_w * V_w; //Intersection


  vec4 P_o = p0_o + t_o * V_o; //Find P_o
  vec4 N_o = P_o;
  N_o.w = 0.0;
  N_o = normalize(N_o);

  //How do we get normal in object space out into world space:
  result.N_w = TRANINVC * N_o;
  result.N_w.w = 0.0;
  result.N_w = normalize(result.N_w);
  //Now we have a point and a normal in world space
  //Then is all we need to do for a phong shader in program




  return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin O and radius r    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V, vec4 O, double r){
  double t   = std::numeric_limits< double >::infinity();
  //TODO: Ray-sphere intersection;

  double t0, t1;
  vec4 subt = p0 - O;

  //V = normalize(V);
  double a = 1;// dot(V, subt);
  double b = dot(2 * V, subt);
  double c = pow(length(subt),2) - pow(r,2);

  t0 = (-b + sqrt(b * b - 4 * a * c)) / 2 * a;
  t1 = (-b - sqrt(b * b - 4 * a * c)) / 2 * a;


  if (t0 > EPSILON && t1 > EPSILON) {
	  t = min(t0, t1);
  }
  else if (t0 < EPSILON && t1 < EPSILON) {
	  t = std::numeric_limits< double >::infinity();
  }
  else if (t0 < EPSILON && t1 > EPSILON) {
	  t = t1;
  }
  else if (t1 < EPSILON && t0 > EPSILON) {
	  t = t0;
  }
  return t;

}




/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0_w, vec4 V_w) {
	IntersectionValues result;
	//TODO: Ray-square setup
	//Transform the ray from world space to object space
	vec4 p0_o = INVC * p0_w;
	vec4 V_o = INVCStar * V_w;
	double len = length(V_o);

	V_o = normalize(V_o);
	double t_o = raySquareIntersection(p0_o, V_o);
	result.t_w = t_o / len;





	//To shade we need to find the intersection point in world space and the normal in world space
	result.P_w = p0_w + result.t_w * V_w; //Intersection


	vec4 P_o = p0_o + t_o * V_o; //Find P_o
	vec4 N_o = vec4(0, 0, 1, 0);

  //How do we get normal in object space out into world space
  result.N_w = TRANINVC * N_o;
  result.N_w.w = 0.0;
  result.N_w = normalize(result.N_w);

  return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V){
  double t   = std::numeric_limits< double >::infinity();
  //TODO: Ray-square intersection;

  vec4 N = vec4(0, 0, 1, 0);
  vec4 S = vec4(0, 0, 0, 1);
  double d = dot(V, N);
  if (abs(d) > EPSILON) {
	  vec4 diff = S - p0;
	  t = dot(N, S - p0) / dot(N, V);
	  vec4 P = p0 + t * V;
	  if (t > EPSILON) {
		  if (abs(P.x) < (1 + EPSILON) && abs(P.y) < (1 + EPSILON)) {
			  return t;
		  }
		  else {
			  return std::numeric_limits< double >::infinity();
		  }
	  }
	  else {
		  return std::numeric_limits< double >::infinity();
	  }
  }
  return t;
}
