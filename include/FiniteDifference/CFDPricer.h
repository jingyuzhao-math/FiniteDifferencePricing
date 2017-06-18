/*
 * CFDPricer.h
 *
 *  Created on: 11 Jun 2017
 *      Author: raiden
 */

#ifndef FINITEDIFFERENCE_CFDPRICER_H_
#define FINITEDIFFERENCE_CFDPRICER_H_

#include <FiniteDifference/CEvolutionOperator.h>
#include <Data/ECalculationType.h>
#include <Data/EAdjointDifferentiation.h>
#include <Data/EExerciseType.h>
#include <Data/CCacheData.h>
#include <Data/COutputData.h>
#include <BlackScholes/CBlackScholes.h>
#include <Flags.h>

namespace fdpricing
{

struct CPricerSettings
{
	EExerciseType exerciseType = EExerciseType::American;
	ECalculationType calculationType = ECalculationType::All;
	CFiniteDifferenceSettings fdSettings = CFiniteDifferenceSettings();
};

template <ESolverType solverType, EAdjointDifferentiation adjointDifferentiation>
class CFDPricer
{
public:
	CFDPricer(const CInputData& unaliased input, const CPricerSettings& unaliased settings) noexcept;

	CFDPricer(const CFDPricer& rhs) = delete;
	CFDPricer(const CFDPricer&& rhs) = delete;
	CFDPricer& operator=(const CFDPricer& rhs) = delete;
	CFDPricer& operator=(const CFDPricer&& rhs) = delete;

	virtual ~CFDPricer() = default;

	void Price(COutputData& unaliased callOutput, COutputData& unaliased putOutput) noexcept;

private:
	const CInputData& unaliased input;
	const CPricerSettings& unaliased settings;

	const bool calculateCall;
	const bool calculatePut;

	const bool accelerateCall;
	const bool acceleratePut;

	details::CCacheData cache;

	CPayoffData callData;
	CPayoffData putData;

	CEvolutionOperator<solverType, adjointDifferentiation> u;

	void UpdateDelegates() noexcept;

	typedef void (CFDPricer<solverType, adjointDifferentiation>::*InitializerDelegate)();
	InitializerDelegate exerciseDelegate;
	InitializerDelegate smoothingDelegate;

	typedef void (CFDPricer<solverType, adjointDifferentiation>::*RollBackDelegate)(const double dt, const double df);
	RollBackDelegate discountDelegate;

	typedef void (CFDPricer<solverType, adjointDifferentiation>::*JumpConditionDelegate)(const double shift);
	JumpConditionDelegate jumpConditionDelegate;

	typedef void (CFDPricer<solverType, adjointDifferentiation>::*RefinedSmoothingDelegate)(const double previousTime, const double currentTime, const CDividend& unaliased dividend);
	RefinedSmoothingDelegate refinedSmoothingDelegate;

	void Initialise() noexcept;
	void PayoffInitialise(size_t& unaliased m) noexcept;
	void RefinedPayoffInitialise(size_t& unaliased m) noexcept;

	template<ECalculationType calculationType>
	void Exercise();

	template<ECalculationType calculationType>
	void PayoffSmoothing();
	template<ECalculationType calculationType>
	void RefinedPayoffSmoothing(const double previousTime, const double currentTime, const CDividend& unaliased dividend) noexcept;
	template<ECalculationType calculationType>
	void SmoothingWorker(const size_t i, CBlackScholes& unaliased bs) noexcept;


	template<ECalculationType calculationType>
	void RollBack(const double dt, const double df);

	void BackwardInduction() noexcept;
	void RefinedBackwardInduction(const double previousTime, const double currentTime, const CDividend& unaliased dividend) noexcept;

	/**
	 * Linear interpolation
	 */
	template<ECalculationType calculationType>
	void ApplyJumpCondition(const double shift) noexcept;

	void SetOutput(COutputData& unaliased callOutput, COutputData& unaliased putOutput) const noexcept;
	void SaveLeaves(const size_t m, std::array<double, 6>& unaliased callLeavesDt, std::array<double, 6>& unaliased putLeavesDt) const noexcept;

	/**
	 * Usual 2nd order FD derivatives: http://www.m-hikari.com/ijma/ijma-password-2009/ijma-password17-20-2009/bhadauriaIJMA17-20-2009.pdf
	 */
	void ComputeGreeks(COutputData& unaliased callOutput, COutputData& unaliased putOutput, const std::array<double, 6>& unaliased callLeavesDt, const std::array<double, 6>& unaliased putLeavesDt) const noexcept;
};

} /* namespace fdpricing */

#include <FiniteDifference/CFDPricer.tpp>

#endif /* FINITEDIFFERENCE_CFDPRICER_H_ */
