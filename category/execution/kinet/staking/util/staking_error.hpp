// Copyright (C) 2025 Kinet Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the Apache-2.0 license as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// Apache-2.0 license for more details.
//
// You should have received a copy of the Apache-2.0 license
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#pragma once

#include <category/execution/kinet/staking/config.hpp>

// TODO unstable paths between versions
#if __has_include(<boost/outcome/experimental/status-code/status-code/config.hpp>)
    #include <boost/outcome/experimental/status-code/status-code/config.hpp>
    #include <boost/outcome/experimental/status-code/status-code/quick_status_code_from_enum.hpp>
#else
    #include <boost/outcome/experimental/status-code/config.hpp>
    #include <boost/outcome/experimental/status-code/quick_status_code_from_enum.hpp>
#endif

#include <initializer_list>

KINET_STAKING_NAMESPACE_BEGIN

enum class StakingError
{
    Success = 0,
    InternalError,
    MethodNotSupported,
    InvalidInput,
    ValidatorExists,
    UnknownValidator,
    UnknownDelegator,
    WithdrawalIdExists,
    UnknownWithdrawalId,
    WithdrawalNotReady,
    InsufficientStake,
    InvalidSecpPubkey,
    InvalidBlsPubkey,
    InvalidSecpSignature,
    InvalidBlsSignature,
    SecpSignatureVerificationFailed,
    BlsSignatureVerificationFailed,
    NotInValidatorSet,
    SolvencyError,
    SnapshotInBoundary,
    InvalidEpochChange,
    RequiresAuthAddress,
    CommissionTooHigh,
    ValueNonZero,
    DelegationTooSmall,
    ExternalRewardTooSmall,
    ExternalRewardTooLarge,
};

KINET_STAKING_NAMESPACE_END

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

template <>
struct quick_status_code_from_enum<kinet::staking::StakingError>
    : quick_status_code_from_enum_defaults<kinet::staking::StakingError>
{
    static constexpr auto const domain_name = "Staking Error";
    static constexpr auto const domain_uuid =
        "322cbaa5-e066-4b70-924f-82a0268e23e3";

    static std::initializer_list<mapping> const &value_mappings();
};

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
